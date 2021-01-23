#pragma once

#include "../vendor/stm32h750xx.h"
#include "../hardware/spi.h"
#include "../types.h"
#include "../delay.h"

/*-------------------------------------*
 * ILI9341 Properties
 *-------------------------------------*/

/* @ Size */

#define ILI9341_WIDTH							240
#define ILI9341_HEIGHT							320

/*-------------------------------------*
 * ILI9341 Commands
 *-------------------------------------*/

/* @ Regulative Command Set */

#define ILI9341_REG_CMD_NOP						0x00
#define ILI9341_REG_CMD_SOFTWARE_RESET			0x01

#define ILI9341_REG_CMD_READ_DISPLAY_ID			0x04
#define ILI9341_REG_CMD_READ_DISPLAY_STATUS		0x09
#define ILI9341_REG_CMD_READ_DISPLAY_POWER_MODE	0x0A
#define ILI9341_REG_CMD_READ_DISPLAY_MADCTL		0x0B
#define ILI9341_REG_CMD_READ_DISPLAY_PXL_FMT		0x0C
#define ILI9341_REG_CMD_READ_DISPLAY_IMG_FORMAT	0x0D
#define ILI9341_REG_CMD_READ_DISPLAY_SIGN_MODE	0x0E
#define ILI9341_REG_CMD_READ_DISPLAY_SELF_DIAG	0x0F

#define ILI9341_REG_CMD_ENTER_SLEEP_MODE			0x10
#define ILI9341_REG_CMD_SLEEP_OUT				0x11
#define ILI9341_REG_CMD_PARTIAL_MODE_ON			0x12
#define ILI9341_REG_CMD_NORMAL_DISPLAY_MODE_ON	0x13

#define ILI9341_REG_CMD_DISPLAY_INVERSION_OFF	0x20
#define ILI9341_REG_CMD_DISPLAY_INVERSION_ON		0x21

#define ILI9341_REG_CMD_GAMMA_SET				0x26

#define ILI9341_REG_CMD_DISPLAY_OFF				0x28
#define ILI9341_REG_CMD_DISPLAY_ON				0x29

#define ILI9341_REG_CMD_COLUMN_ADDRESS_SET		0x2A
#define ILI9341_REG_CMD_PAGE_ADDRESS_SET			0x2B
#define ILI9341_REG_CMD_MEMORY_WRITE				0x2C

#define ILI9341_REG_CMD_COLOR_SET				0x2D

#define ILI9341_REG_CMD_MEMORY_READ				0x2E
#define ILI9341_REG_CMD_PARTIAL_AREA				0x30

#define ILI9341_REG_CMD_VERTICAL_SCROLLING_DEF	0x33

#define ILI9341_REG_CMD_TEARING_EFFECT_LINE_OFF	0x34
#define ILI9341_REG_CMD_TEARING_EFFECT_LINE_ON	0x35

#define ILI9341_REG_CMD_MEMORY_ACCESS_CONTROL	0x36

#define ILI9341_REG_CMD_VSCROLL_START_ADDR		0x37

#define ILI9341_REG_CMD_IDLE_MODE_OFF			0x38
#define ILI9341_REG_CMD_IDLE_MODE_ON				0x39

#define ILI9341_REG_CMD_PIXEL_FORMAT_SET			0x3A

#define ILI9341_REG_CMD_WRITE_MEMORY_CONTINUE	0x3C
#define ILI9341_REG_CMD_READ_MEMORY_CONTINUE		0x3E

#define ILI9341_REG_CMD_SET_TEAR_SCANLINE		0x44
#define ILI9341_REG_CMD_GET_SCANLINE				0x45

#define ILI9341_REG_CMD_WRITE_DISPLAY_BRIGHTNESS	0x51
#define ILI9341_REG_CMD_READ_DISPLAY_BRIGHTNESS	0x52

#define ILI9341_REG_CMD_WRITE_CTRL_DISPLAY		0x53
#define ILI9341_REG_CMD_READ_CTRL_DISPLAY		0x54

#define ILI9341_REG_CMD_W_CNT_ADAP_B_CTRL		0x55
#define ILI9341_REG_CMD_R_CNT_ADAP_B_CTRL		0x56

#define ILI9341_REG_CMD_W_CABC_MIN_BRIGHTNESS	0x5E
#define ILI9341_REG_CMD_R_CABC_MIN_BRIGHTNESS	0x5F

#define ILI9341_REG_CMD_READ_ID1					0xDA
#define ILI9341_REG_CMD_READ_ID2					0xDB
#define ILI9341_REG_CMD_READ_ID3					0xDC

/* @ Extended Command Set  */

#define ILI9341_EXT_CMD_RGB_INTERFACE_SIGN_CTRL	0xB0
#define ILI9341_EXT_CMD_FRAME_CONTROL_NORMAL		0xB1
#define ILI9341_EXT_CMD_FRAME_CONTROL_IDLE		0xB2
#define ILI9341_EXT_CMD_FRAME_CONTROL_PARTIAL	0xB3
#define ILI9341_EXT_CMD_DISPLAY_INVERS_CTRL		0xB4
#define ILI9341_EXT_CMD_BLANKING_PORCH_CTRL		0xB5
#define ILI9341_EXT_CMD_DISPLAY_FUNCTION_CTRL	0xB6
#define ILI9341_EXT_CMD_ENTRY_MODE_SET			0xB7

#define ILI9341_EXT_CMD_POSITIVE_GAMMA_COR		0xE0
#define ILI9341_EXT_CMD_NEGATIVE_GAMMA_COR		0xE1

/*-------------------------------------*
 * ILI9341 Driver
 *-------------------------------------*/

namespace Drivers
{
	typedef struct
	{
		unsigned red 	: 6;
		unsigned green 	: 6;
		unsigned blue	: 6;
	} ILI9341_Color_t;

	class ILI9341
	{
	public:
		/*----------------*
		 * Class stuff
		 *----------------*/

		ILI9341(Hardware::SPI &spi, volatile GPIO_TypeDef *gpio, u8 reset, u8 dc) noexcept;

		/*----------------*
		 * Commands
		 *----------------*/

		void command(u8 command) noexcept;
		void data(u8 data);
		void data(u16 data1, u16 data2);
		void data(u8 *data, u8 cnt);

		/*----------------*
		 * Resets
		 *----------------*/

		void softwareReset(void) noexcept;
		void hardwareReset(void) noexcept;

		/*----------------*
		 * Initialization
		 *----------------*/

		void init(void) noexcept;

		/*----------------*
		 * Drawing
		 *----------------*/

		void drawNumber(const ILI9341_Color_t &color, u16 x, u16 y, u8 n);
		void drawPixel(const ILI9341_Color_t &color, u16 x, u16 y);
		void drawBitmap(const ILI9341_Color_t &color, u8 *bitmap, u16 sx, u16 sy, u8 cnt);

		/*----------------*
		 * Operations
		 *----------------*/

		void setColumnAddress(u16 sx, u16 ex) noexcept;
		void setRowAddress(u16 sy, u16 ey) noexcept;

		void writePixel(const ILI9341_Color_t &color) noexcept;
		void drawSquare(const ILI9341_Color_t &color, u16 sx, u16 ex, u16 sy, u16 ey);
		void clear(const ILI9341_Color_t &color) noexcept;
	private:
		Hardware::SPI &m_SPI;
		volatile GPIO_TypeDef *m_GPIO;
		u8 m_Reset, m_DC;
	};
}
