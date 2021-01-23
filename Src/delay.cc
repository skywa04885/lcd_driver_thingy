#include "delay.h"

void Delay::init(void) noexcept
{
	DELAY_TIMER->PSC = 120;
	DELAY_TIMER->CR1 = 0;
}

void Delay::us(u32 us) noexcept
{

	DELAY_TIMER->ARR = us;
	DELAY_TIMER->CNT = 0;
	DELAY_TIMER->SR = 0;
	DELAY_TIMER->CR1 |= TIM_CR1_CEN | TIM_CR1_OPM;

	while (!(DELAY_TIMER->SR & TIM_SR_UIF));
}

void Delay::ms(u32 ms) noexcept
{
	for (u16 i = 0; i < ms; ++i)
		Delay::us(1000);
}

void Delay::s(u32 s) noexcept
{
	for (u32 i = 0; i < s; ++i)
		Delay::ms(1000);
}
