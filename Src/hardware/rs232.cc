#include <hardware/rs232.h>

extern "C" int __io_putchar(int ch)
{
	Hardware::RS232::write(static_cast<char>(ch));
	return ch;
}

namespace Hardware
{
	#define RS232_BUS_CLK (120 * 1000000)
	void RS232::init(u32 baud) noexcept
	{
		// Calculate & Set BAUD rate
		USART1->BRR = (((2 * RS232_BUS_CLK) + baud) / (2 * baud));

		// Enable RX interrupt, and enable USART1 in NVIC
		USART1->CR1 |= USART_CR1_RXNEIE_RXFNEIE;
		NVIC_EnableIRQ(USART1_IRQn);

		// Enable USART1
		USART1->CR1 = USART_CR1_TE | USART_CR1_UE;
	}

	void RS232::write(char c) noexcept
	{
		if (c == '\n')
			RS232::write('\r');

		// Write the char
		USART1->TDR = static_cast<u32>(c);
		while (!(USART1->ISR & USART_ISR_TC));
	}

	void RS232::write(const char *p) noexcept
	{
		while (*p != '\0')
			RS232::write(*p++);
	}
}
