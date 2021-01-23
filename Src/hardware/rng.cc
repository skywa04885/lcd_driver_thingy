#include <stdio.h>
#include "hardware/rng.h"

namespace Hardware
{
	/**
	 * Initializes the True Random Number Generator
	 */
	void RandomNumberGenerator::init(void)
	{
		// Selects RNG clock source
		RCC->D2CCIP2R |= RCC_D2CCIP2R_RNGSEL_0;

		// Enables clock for RNG
		RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
	}

	/**
 	 * Generates an 32-bit random number
 	 */
	u32 RandomNumberGenerator::generate(void)
	{
		RNG->CR |= RNG_CR_RNGEN;

		for (;;)
		{
			if (RNG->SR & RNG_SR_DRDY) break;
			else if (RNG->SR & (RNG_SR_SEIS | RNG_SR_CEIS))
			{
				printf("error\n");
				break;
			}
		}

		u32 res = RNG->DR;

		RNG->CR &= ~RNG_CR_RNGEN;

		return res;
	}
}
