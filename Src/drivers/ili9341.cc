#include "drivers/ili9341.h"

namespace Drivers
{
	static u8 number_bitmap[10][5] = {
			{
					0b01111110,
					0b01100110,
					0b01100110,
					0b01100110,
					0b01111110
			},
			{
					0b00110000,
					0b01110000,
					0b00010000,
					0b00010000,
					0b00111000
			},
			{
					0b01111110,
					0b00000010,
					0b01111110,
					0b01000000,
					0b01111110
			},
			{
					0b00111100,
					0b00000010,
					0b00011100,
					0b00000010,
					0b00111100
			},
			{
					0b01100110,
					0b01100110,
					0b01111110,
					0b00001110,
					0b00001110
			},
			{
					0b01111100,
					0b01000000,
					0b01111100,
					0b00000100,
					0b01111100
			},
			{
					0b01100000,
					0b01000000,
					0b01111100,
					0b01000100,
					0b01111100
			},
			{
					0b01111110,
					0b00000110,
					0b00111110,
					0b00011000,
					0b00110000
			},
			{
					0b01111110,
					0b01100110,
					0b01111110,
					0b01100110,
					0b01111110
			},
			{
					0b01111110,
					0b01100110,
					0b01111110,
					0b00000110,
					0b00000110
			}
	};

	/*----------------*
	 * Class stuff
	 *----------------*/

	ILI9341::ILI9341(Hardware::SPI &spi, volatile GPIO_TypeDef *gpio, u8 reset, u8 dc) noexcept:
			m_SPI(spi),
			m_GPIO(gpio),
			m_Reset(reset),
			m_DC(dc)
	{}

	/*----------------*
	 * Commands
	 *----------------*/

	void ILI9341::command(u8 command) noexcept
	{
		m_SPI.start();

		m_GPIO->ODR &= ~_BV(m_DC);
		m_SPI.write8(command);

		m_SPI.await();
		m_SPI.stop();
	}

	void ILI9341::data(u8 data)
	{
		m_SPI.start();

		m_GPIO->ODR |= _BV(m_DC);
		m_SPI.write8(data);

		m_SPI.await();
		m_SPI.stop();
	}

	void ILI9341::data(u16 data1, u16 data2)
	{
		m_SPI.start();

		m_GPIO->ODR |= _BV(m_DC);
		m_SPI.write8(static_cast<u8>(data1 >> 8));
		m_SPI.write8(static_cast<u8>(data1));

		m_SPI.write8(static_cast<u8>(data2 >> 8));
		m_SPI.write8(static_cast<u8>(data2));

		m_SPI.await();
		m_SPI.stop();
	}

	void ILI9341::data(u8 *data, u8 cnt)
	{
		m_SPI.start();

		m_GPIO->ODR |= _BV(m_DC);

		for (u8 i = 0; i < cnt; ++i)
			m_SPI.write8(data[i]);

		m_SPI.await();
		m_SPI.stop();
	}

	/*----------------*
	 * Resets
	 *----------------*/

	void ILI9341::softwareReset(void) noexcept
	{
		command(ILI9341_REG_CMD_SOFTWARE_RESET);
		Delay::ms(20);
	}

	void ILI9341::hardwareReset(void) noexcept
	{
		m_GPIO->ODR &= ~_BV(m_Reset);
		Delay::ms(20);
		m_GPIO->ODR |= _BV(m_Reset);
		Delay::ms(20);
	}

	/*----------------*
	 * Initialization
	 *----------------*/

	void ILI9341::init(void) noexcept
	{
		//
		// Resets ILI9341
		//

		// Performs hard reset
		hardwareReset();

		// Performs soft reset
		softwareReset();

		//
		// AdaFruit default gamma
		//

		u8 posGammaCorrection[] = {
				0x0F, 0x31, 0x2B,
				0x0C, 0x0E, 0x08,
				0x4E, 0xF1, 0x37,
				0x07, 0x10, 0x03,
				0x0E, 0x09, 0x00
		};

		u8 negGammaCorrection[] = {
				0x00, 0x0E, 0x14,
				0x03, 0x11, 0x07,
				0x31, 0xC1, 0x48,
				0x08, 0x0F, 0x0C,
				0x31, 0x36, 0x0F
		};

		// Gamma set
		ILI9341::command(ILI9341_REG_CMD_GAMMA_SET);
		ILI9341::data(0x01);

		// Positive gamma correction
		ILI9341::command(ILI9341_EXT_CMD_POSITIVE_GAMMA_COR);
		ILI9341::data(posGammaCorrection, sizeof (posGammaCorrection) / sizeof (u8));

		// Negative gamma correction
		ILI9341::command(ILI9341_EXT_CMD_NEGATIVE_GAMMA_COR);
		ILI9341::data(negGammaCorrection, sizeof (negGammaCorrection) / sizeof (u8));

		//
		// Enable ILI9341
		//

		// Sleep out
		ILI9341::command(ILI9341_REG_CMD_SLEEP_OUT);
		Delay::ms(20);

		// Display on
		ILI9341::command(ILI9341_REG_CMD_DISPLAY_ON);
		Delay::ms(20);

		// Normal mode
		ILI9341::command(ILI9341_REG_CMD_NORMAL_DISPLAY_MODE_ON);
	}

	/*----------------*
	 * Drawing
	 *----------------*/

	void ILI9341::drawNumber(const ILI9341_Color_t &color, u16 x, u16 y, u8 n)
	{
		if (n > 9) return;

		ILI9341::drawBitmap(color, number_bitmap[n], x, y, 5);
	}

	void ILI9341::drawPixel(const ILI9341_Color_t &color, u16 x, u16 y)
	{
		//
		// Sets the position
		//

		// Sets the X and Y
		setColumnAddress(x, x);
		setRowAddress(y, y);

		// Sends the write command
		command(ILI9341_REG_CMD_MEMORY_WRITE);

		//
		// Sends the pixel
		//

		m_SPI.start();
		m_GPIO->ODR |= _BV(m_DC);

		writePixel(color);

		m_SPI.await();
		m_SPI.stop();
	}

	void ILI9341::drawBitmap(const ILI9341_Color_t &color, u8 *bitmap, u16 sx, u16 sy, u8 cnt)
	{
		for (u8 bmp_row = 0; bmp_row < cnt; ++bmp_row)
		{
			u8 bmp_row_v = bitmap[bmp_row];

			for (u8 bmp_col = 0; bmp_col < 8; ++bmp_col)
			{
				if (bmp_row_v & 1)
					drawPixel(color, sx + bmp_col, sy + bmp_row);

				bmp_row_v >>= 1;
			}
		}
	}

	/*----------------*
	 * Operations
	 *----------------*/

	void ILI9341::setColumnAddress(u16 sx, u16 ex) noexcept
	{
		ILI9341::command(ILI9341_REG_CMD_COLUMN_ADDRESS_SET);
		ILI9341::data(sx, ex);
	}

	void ILI9341::setRowAddress(u16 sy, u16 ey) noexcept
	{
		ILI9341::command(ILI9341_REG_CMD_PAGE_ADDRESS_SET);
		ILI9341::data(sy, ey);
	}

	void ILI9341::writePixel(const ILI9341_Color_t &color) noexcept
	{
		m_SPI.write8(color.blue << 2);
		m_SPI.write8(color.green << 2);
		m_SPI.write8(color.red << 2);
	}

	void ILI9341::drawSquare(const ILI9341_Color_t &color, u16 sx, u16 ex, u16 sy, u16 ey)
	{
		//
		// Sets the addresses
		//

		setColumnAddress(sx, ex);
		setRowAddress(sy, ey);

		//
		// Writes the square
		//

		command(ILI9341_REG_CMD_MEMORY_WRITE);

		m_SPI.start();
		m_GPIO->ODR |= _BV(m_DC);
		for (u16 x = sx; x <= ex; ++x)
		{
			for (u16 y = sy; y <= ey; ++y)
			{
				writePixel(color);
			}
		}

		m_SPI.await();
		m_SPI.stop();
	}

	void ILI9341::clear(const ILI9341_Color_t &color) noexcept
	{
		ILI9341::drawSquare(color, 0, ILI9341_WIDTH, 0, ILI9341_HEIGHT);
	}
}
