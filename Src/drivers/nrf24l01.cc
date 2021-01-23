#include "drivers/nrf24l01.h"

namespace Drivers::NordicSemi
{
	NRF24L01::NRF24L01(NRF24L01_Config_t config, SPI &spi, volatile GPIO_TypeDef *gpio, u8 ce) noexcept :
			m_Config(config), m_SPI(spi), m_GPIO(gpio), m_CE(ce)
	{}

	/*-----------------------------*
	 * Default functions
	 *-----------------------------*/

	void NRF24L01::init(void) noexcept
	{
		//
		// Performs configuration
		//

		// Sets the RX/TX address size to 5 bytes
		NRF24L01::registerWrite(NRF24L01_REGISTER_SETUP_AW, NRF24L01_RBIT_SETUP_AW_AW(0b11));

		// Tells the device what our address is
		NRF24L01::bufferWrite(NRF24L01_REGISTER_RX_PW_P0, m_Config.address, 5);

		// Sets the auto-retransmit options, delay: 750us and retransmission count
		//  to 8 times
		NRF24L01::registerWrite(NRF24L01_REGISTER_SETUP_RETR, (NRF24L01_RBIT_SETUP_RETR_ARDA(0b0010)
				| NRF24L01_RBIT_SETUP_RETR_ARC(0b1111)));

		// Sets the frequency channel
		NRF24L01::registerWrite(NRF24L01_REGISTER_RF_CH, NRF24L01_RBIT_RF_CH(m_Config.channel));

		// Sets the RF power to  and speed to 1Mbps
		NRF24L01::registerWrite(NRF24L01_REGISTER_RF_SETUP, (NRF24L01_RBIT_RF_PWR(0b11)
				| _BV(NRF24L01_RBIT_RF_SETUP_RF_DR_LOW)));

		// Enable dynamic data length
		NRF24L01::registerWrite(NRF24L01_REGISTER_FEATURE, _BV(NRF24L01_RBIT_FEATURE_EN_DPL));

		// Enabled dynamic data length on all channels
		NRF24L01::registerWrite(NRF24L01_REGISTER_DYNDP, _BV(NRF24L01_RBIT_DYNP_P0)
				| _BV(NRF24L01_RBIT_DYNP_P1)
				| _BV(NRF24L01_RBIT_DYNP_P2)
				| _BV(NRF24L01_RBIT_DYNP_P3)
				| _BV(NRF24L01_RBIT_DYNP_P4)
				| _BV(NRF24L01_RBIT_DYNP_P5));


		//
		// Other stuff
		//

		// Sends test packet
		u8 address[5] = { 0x21, 0x22, 0x23, 0x24, 0x25 };
		u8 payload[] = { 'F', 'u', 'c', 'k', '_', 'm', 'e' };
		transmit(address, payload, sizeof (payload));
	}

	void NRF24L01::transmit(u8 *address, u8 *payload, u8 plen) noexcept
	{
		//
		// Prepares for transmission
		//

		// Goes into TX mode
		NRF24L01::registerClear(NRF24L01_REGISTER_CONFIG,
				_BV(NRF24L01_RBIT_CONFIG_PRIM_RX));

		// Writes the destination address of the packet, and the data
		//  after it
		NRF24L01::bufferWrite(NRF24L01_REGISTER_TX_ADDR, address, 5);
		NRF24L01::payloadWrite(payload, plen);

		//
		// Transmits
		//

		// Sends a 10 us pulse to the CE pin
		m_GPIO->ODR |= _BV(m_CE);
		Delay::us(50);
		m_GPIO->ODR &= ~_BV(m_CE);

		//
		// Finishes
		//

		// Waits for the ACK
		while (!(NRF24L01::registerRead(NRF24L01_REGISTER_STATUS) & _BV(NRF24L01_RBIT_STATUS_TX_DS)));
	}

	/*-----------------------------*
	 * Register modification
	 *-----------------------------*/

	void NRF24L01::registerWrite(u8 reg, u8 value) noexcept
	{
		m_SPI.start();

		m_SPI.write8(NRF24L01_COMMAND_W_REGISTER);
		m_SPI.write8(reg);
		m_SPI.write8(value);

		m_SPI.await();
		m_SPI.stop();
	}

	void NRF24L01::registerSet(u8 reg, u8 mask) noexcept
	{
		u8 val = NRF24L01::registerRead(reg);
		val |= mask;
		NRF24L01::registerWrite(reg, val);
	}

	void NRF24L01::registerClear(u8 reg, u8 mask) noexcept
	{
		u8 val = NRF24L01::registerRead(reg);
		val &= ~mask;
		NRF24L01::registerWrite(reg, val);
	}

	u8 NRF24L01::registerRead(u8 reg) noexcept
	{
		m_SPI.start();

		m_SPI.trans8(NRF24L01_COMMAND_R_REGISTER);
		m_SPI.trans8(reg);
		u8 val = m_SPI.trans8(0xFF);

		m_SPI.await();
		m_SPI.stop();

		return val;
	}

	/*-----------------------------*
	 * Buffer modification
	 *-----------------------------*/

	void NRF24L01::bufferWrite(u8 reg, u8 *data, u8 dlen) noexcept
	{
		m_SPI.start();

		m_SPI.write8(NRF24L01_COMMAND_W_REGISTER);
		m_SPI.write8(reg);
		for (u8 i = 0; i < dlen; ++i)
			m_SPI.write8(data[i]);

		m_SPI.await();
		m_SPI.stop();
	}

	void NRF24L01::payloadWrite(u8 *data, u8 dlen) noexcept
	{
		m_SPI.start();

		m_SPI.write8(NRF24L01_COMMAND_W_TX_PAYLOAD);
		for (u8 i = 0; i < dlen; ++i)
			m_SPI.write8(data[i]);

		m_SPI.await();
		m_SPI.stop();
	}
}
