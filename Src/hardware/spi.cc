#include "hardware/spi.h"

namespace Hardware
{
	SPI::SPI(volatile SPI_TypeDef *spi) noexcept:
			m_SPI(spi)
	{}

	void SPI::init(void) noexcept
	{
		//
		// Configure Procedure
		//

		// Sets the master BAUD Rate
		m_SPI->CFG1 &= ~SPI_CFG1_MBR;
		m_SPI->CFG1 |= (0b101 << SPI_CFG1_MBR_Pos);		// clock / 64

		// Slave select pin master mode
		m_SPI->CFG2 |= SPI_CFG2_SSOE;

		// Master InterFrame idleness
		m_SPI->CFG2 &= ~SPI_CFG2_MIDI;
		m_SPI->CFG2 |= (4 << SPI_CFG2_MIDI_Pos);		// 4 Clock-Cycle delay between frames

		// Master SlaveSelect idleness
		m_SPI->CFG2 &= ~SPI_CFG2_MSSI;
		m_SPI->CFG2 |= (0 << SPI_CFG2_MSSI_Pos);

		// Transmit sequence size
		m_SPI->CR2 &= ~SPI_CR2_TSIZE;					// Size not known

		// Number of bits in a single data frame
		m_SPI->CFG1 &= ~SPI_CFG1_DSIZE;
		m_SPI->CFG1 |= (0b00111 << SPI_CFG1_DSIZE_Pos);	// 8-bits

		// Number of data frames at single data packet
		m_SPI->CFG1 &= ~SPI_CFG1_FTHLV;
		m_SPI->CFG1 |= (0b0010 << SPI_CFG1_FTHLV_Pos);	// 2-data ( 16-bit )

		//
		// Enable Procedure
		//

		// Enable master
		m_SPI->CFG2 |= SPI_CFG2_MASTER;

		// Enable SPI1
		m_SPI->CR1 |= SPI_CR1_SPE;
	}

	void SPI::start(void) noexcept
	{
		m_SPI->CR1 |= SPI_CR1_SPE;
		m_SPI->CR1 |= SPI_CR1_CSTART;
	}

	void SPI::stop(void) noexcept
	{
		m_SPI->CR1 |= SPI_CR1_CSUSP;
		m_SPI->CR1 &= ~SPI_CR1_SPE;
	}

	void SPI::await(void) noexcept
	{
		while (!(m_SPI->SR & SPI_SR_TXC));
	}

	void SPI::write8(u8 b) noexcept
	{
		while (!(m_SPI->SR & SPI_SR_TXP));
		*(reinterpret_cast<volatile u8 *>(&m_SPI->TXDR)) = b;
	}

	u8 SPI::trans8(u8 b) noexcept
	{
		while (!(m_SPI->SR & SPI_SR_TXP));
		*(reinterpret_cast<volatile u8 *>(&m_SPI->TXDR)) = b;

		while (!(m_SPI->SR & SPI_SR_RXP));
		return *(reinterpret_cast<volatile u8 *>(&m_SPI->RXDR));
	}
}
