#pragma once

#include "vendor/stm32h750xx.h"
#include "types.h"

#define DELAY_TIMER TIM2

class Delay
{
public:
	static void init(void) noexcept;

	static void us(u32 us) noexcept;
	static void ms(u32 ms) noexcept;
	static void s(u32 s) noexcept;
};
