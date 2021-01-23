#pragma once

#include "../vendor/stm32h750xx.h"
#include "../types.h"

namespace Hardware
{
	class RandomNumberGenerator
	{
	public:
		/**
		 * Initializes the True Random Number Generator
		 */
		static void init(void);

		/**
		 * Generates an 32-bit random number
		 */
		static u32 generate(void);
	};
}
