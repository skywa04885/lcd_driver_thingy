#pragma once

#include "../vendor/stm32h750xx.h"
#include "../types.h"
#include "fifo.h"

namespace Hardware
{
	class RS232
	{
	public:
		static void init(u32 baud) noexcept;

		static void write(char c) noexcept;
		static void write(const char *p) noexcept;
	};
}
