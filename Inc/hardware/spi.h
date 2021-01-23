#pragma once

#include "../vendor/stm32h750xx.h"
#include "../types.h"

namespace Hardware
{
	class SPI
	{
	public:
		SPI(volatile SPI_TypeDef *spi) noexcept;

		void init(void) noexcept;

		void start(void) noexcept;
		void stop(void) noexcept;
		void await(void) noexcept;

		void write8(u8 b) noexcept;
		u8 trans8(u8 b) noexcept;
	private:
		volatile SPI_TypeDef *m_SPI;
	};
}
