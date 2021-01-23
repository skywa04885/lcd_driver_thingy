#include <stdint.h>
#include <stdio.h>

#include "hardware/rs232.h"
#include "hardware/rng.h"
#include "hardware/rtc.h"

#include "types.h"
#include "helpers/gpio.h"
#include "vendor/stm32h750xx.h"

#include "hardware/spi.h"
#include "drivers/ili9341.h"
#include "drivers/nrf24l01.h"

#include "delay.h"
#include "sysclk.h"

extern u8 eth_connected_bitmap[7];

void setup(void)
{
	sysclk_init();

	//
	// Enables clocks
	//

	// Enables used USART's
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// Enables used GPIO's
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN;

	// Enables all the SPI's
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// Enables all the Timers
	RCC->APB1LENR |= RCC_APB1LENR_TIM2EN | RCC_APB1LENR_SPI2EN;

	//
	// Initialize RS232
	//

	// Configure the RS232 RX/TX pins ( PA10, PA9 )
	GPIOA->MODER &= ~((GPIO_MODE_MASK << GPIO_MODER_MODE10_Pos) |
			(GPIO_MODE_MASK << GPIO_MODER_MODE9_Pos));

	GPIOA->MODER |= ((GPIO_MODE_AF << GPIO_MODER_MODE10_Pos) |
			(GPIO_MODE_AF << GPIO_MODER_MODE9_Pos));

	GPIOA->AFR[1] |= ((7 << GPIO_AFRH_AFSEL9_Pos) |
			(7 << GPIO_AFRH_AFSEL9_Pos));

	// Configure the RS232 USART
	Hardware::RS232::init(115200);
	printf("RS232 Ready\n");

	//
	// Initialize other stuff
	//

	Hardware::RandomNumberGenerator::init();
	Hardware::RTCDriver::init();
	Delay::init();
}

#define LCD_GPIO			GPIOA
#define LCD_RESET 		2
#define LCD_DC			3
#define LCD_CS			4
#define LCD_SCK			5
#define LCD_MISO			6
#define LCD_MOSI			7

#define NRF24L01_GPIO	GPIOB
#define NRF24L01_CE		11
#define NRF24L01_CS		12
#define NRF24L01_SCK		13
#define NRF24L01_MISO	14
#define NRF24L01_MOSI	15

static Drivers::NordicSemi::NRF24L01_Config_t nrf24l01Config = {
		.address = { 0x23, 0x44, 0x11, 0x12, 0x55 },
		.channel = 11
};

static Hardware::SPI lcd_spi(SPI1), nrf24l01SPI(SPI2);

static Drivers::ILI9341 lcdDriver(lcd_spi, LCD_GPIO, LCD_RESET, LCD_DC);
static Drivers::NordicSemi::NRF24L01 nrf24l01Driver(nrf24l01Config, nrf24l01SPI,
		NRF24L01_GPIO, NRF24L01_CE);

void lcd_init(void)
{
	//
	// Configure SPI1 GPIO
	//

	// Reset all GPIO's
	LCD_GPIO->MODER &= ~((GPIO_MODE_MASK << (2 * LCD_RESET))
			| (GPIO_MODE_MASK << (2 * LCD_DC))
			| (GPIO_MODE_MASK << (2 * LCD_CS))
			| (GPIO_MODE_MASK << (2 * LCD_SCK))
			| (GPIO_MODE_MASK << (2 * LCD_MISO))
			| (GPIO_MODE_MASK << (2 * LCD_MOSI)));

	// Sets the actual pin modes
	LCD_GPIO->MODER |= ((GPIO_MODE_OUTPUT << (2 * LCD_RESET))
			| (GPIO_MODE_OUTPUT << (2 * LCD_DC))
			| (GPIO_MODE_AF << (2 * LCD_CS))
			| (GPIO_MODE_AF << (2 * LCD_SCK))
			| (GPIO_MODE_AF << (2 * LCD_MISO))
			| (GPIO_MODE_AF << (2 * LCD_MOSI)));

	// Sets the default pin values
	LCD_GPIO->ODR |= _BV(LCD_RESET); // Reset is Active Low

	// Resets the default PUPD
	LCD_GPIO->PUPDR &= ~((GPIO_PUPDR_RESET << (2 * LCD_RESET))
			| (GPIO_PUPDR_RESET << (2 * LCD_DC)));

	// Sets pull down
	LCD_GPIO->PUPDR |= ((GPIO_PUPDR_PULLDOWN << (2 * LCD_RESET))
			| (GPIO_PUPDR_PULLDOWN << (2 * LCD_DC)));

	// Selects the alternative functions
	LCD_GPIO->AFR[0] |= ((5 << (LCD_CS * 4))
			| (5 << (LCD_SCK * 4))
			| (5 << (LCD_MISO * 4))
			| (5 << (LCD_MOSI * 4)));

	//
	// Configure SPI2 GPIO
	//

	// Resets the GPIO's
	NRF24L01_GPIO->MODER &= ~((GPIO_MODE_MASK << (2 * NRF24L01_CS))
			| (GPIO_MODE_MASK << (2 * NRF24L01_SCK))
			| (GPIO_MODE_MASK << (2 * NRF24L01_MISO))
			| (GPIO_MODE_MASK << (2 * NRF24L01_MOSI))
			| (GPIO_MODE_MASK << (2 * NRF24L01_CE)));

	// Sets the actual pin modes
	NRF24L01_GPIO->MODER |= ((GPIO_MODE_AF << (2 * NRF24L01_CS))
			| (GPIO_MODE_AF << (2 * NRF24L01_SCK))
			| (GPIO_MODE_AF << (2 * NRF24L01_MISO))
			| (GPIO_MODE_AF << (2 * NRF24L01_MOSI))
			| (GPIO_MODE_OUTPUT << (2 * NRF24L01_CE)));

	// Selects the alternative functions
	NRF24L01_GPIO->AFR[1] |= ((5 << ((NRF24L01_CS - 8) * 4))
			| (5 << ((NRF24L01_SCK - 8) * 4))
			| (5 << ((NRF24L01_MISO - 8) * 4))
			| (5 << ((NRF24L01_MOSI - 8) * 4)));

	// Resets the default PUPD
	NRF24L01_GPIO->PUPDR &= ~((GPIO_PUPDR_RESET << (2 * NRF24L01_CE)));

	// Sets pull down
	NRF24L01_GPIO->PUPDR |= ((GPIO_PUPDR_PULLDOWN << (2 * NRF24L01_CE)));

	//
	// Initializes the SPI & ILI9341 driver
	//

	lcd_spi.init();
	nrf24l01SPI.init();

	// Performs LCD initialization
	lcdDriver.init();
}

#define HEIGHT_CHAR 5
#define TASKBAR_PADDING 10
#define TASKBAR_HEIGHT (HEIGHT_CHAR + (2 * TASKBAR_PADDING))

#define BUTTON_PADDING 10

static u8 colon[5] = {
		0b00111000,
		0b00010000,
		0b00000000,
		0b00010000,
		0b00111000
};

extern "C" int main(void)
{
	setup();
	lcd_init();

    /* Loop forever */
	Drivers::ILI9341_Color_t white;
	white.red = 0b111111 - 6;
	white.blue = 0b111111 - 6;
	white.green = 0b111111 - 6;

	Drivers::ILI9341_Color_t gray;
	gray.red = 0b111111 - 40;
	gray.blue = 0b111111 - 40;
	gray.green = 0b111111 - 40;

	Drivers::ILI9341_Color_t color;
	color.red = 4;
	color.blue = 4;
	color.green = 4;

	// Draws the background colors
	lcdDriver.clear(white);
	lcdDriver.drawSquare(color, 0, ILI9341_WIDTH, 0, TASKBAR_HEIGHT);

	// Puts the connected icon
	lcdDriver.drawBitmap(white, eth_connected_bitmap, 10, TASKBAR_PADDING, 7);

	// Puts the button
	lcdDriver.drawSquare(gray, BUTTON_PADDING, ILI9341_WIDTH - BUTTON_PADDING, TASKBAR_HEIGHT + BUTTON_PADDING, TASKBAR_HEIGHT + BUTTON_PADDING + 40);

	// Starts the main loop
	u8 seconds_prev = 255;
	for(;;)
	{
		Hardware::RTC_Time_t time = Hardware::RTCDriver::getTime();

		// Update taskbar every second
		if (time.seconds != seconds_prev)
		{
			seconds_prev = time.seconds;

			// Clears the taskbar background
			lcdDriver.drawSquare(color, ILI9341_WIDTH - TASKBAR_PADDING - 56, ILI9341_WIDTH, 0, TASKBAR_HEIGHT);

			// Seconds
			lcdDriver.drawNumber(white, ILI9341_WIDTH - TASKBAR_PADDING, TASKBAR_PADDING, time.seconds / 10);
			lcdDriver.drawNumber(white, ILI9341_WIDTH - TASKBAR_PADDING - 8, TASKBAR_PADDING, time.seconds % 10);

			// Colon
			lcdDriver.drawBitmap(white, colon, ILI9341_WIDTH - TASKBAR_PADDING - 16, TASKBAR_PADDING, 5);

			// Minutes
			lcdDriver.drawNumber(white, ILI9341_WIDTH - TASKBAR_PADDING - 24, TASKBAR_PADDING, time.minutes / 10);
			lcdDriver.drawNumber(white, ILI9341_WIDTH - TASKBAR_PADDING - 32, TASKBAR_PADDING, time.minutes % 10);

			// Colon
			lcdDriver.drawBitmap(white, colon, ILI9341_WIDTH - TASKBAR_PADDING - 40, TASKBAR_PADDING, 5);

			// Hoyrs
			lcdDriver.drawNumber(white, ILI9341_WIDTH - TASKBAR_PADDING - 48, TASKBAR_PADDING, time.hours / 10);
			lcdDriver.drawNumber(white, ILI9341_WIDTH - TASKBAR_PADDING - 56, TASKBAR_PADDING, time.hours % 10);

		}
	}
}
