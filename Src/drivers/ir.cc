#include "drivers/ir.h"

extern "C" void EXTI2_IRQHandler(void) noexcept
{

}

namespace Drivers
{
	void RC5Receiver::init(volatile GPIO_TypeDef *gpio, u8 s) noexcept
	{
		//
		// Configures EXTI
		//
	}
}
