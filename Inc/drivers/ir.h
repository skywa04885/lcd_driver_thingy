#pragma once

#include "../vendor/stm32h750xx.h"
#include "../types.h"

namespace Drivers
{
	typedef struct
	{
		unsigned 	s 	: 1;	/* Start-Bit */
		unsigned	f	: 1;	/* Field-Bit */
		unsigned 	c	: 1;	/* Control bit or Toggle bit */
		unsigned	adr	: 5;	/* Address */
		unsigned	cmd	: 6;	/* Command */
	} RC5_Frame_t;

	typedef struct
	{
		unsigned	s	: 1;	/* Start-Bit */
		unsigned	cmd	: 1;	/* Command */
		unsigned	adr	: 1;	/* Address */
	} SIRC_Frame_t;

	class RC5Receiver
	{
	public:
		void init(volatile GPIO_TypeDef *gpio, u8 s) noexcept;

		SIRC_Frame_t read(void);
	private:
	};
}
