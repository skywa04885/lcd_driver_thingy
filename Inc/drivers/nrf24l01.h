#pragma once

#include "../types.h"
#include "../hardware/spi.h"
#include "../delay.h"

/*-------------------------------------*
 * NRF24L01 Commands
 *-------------------------------------*/

#define NRF24L01_COMMAND_R_REGISTER				0b00000000
#define NRF24L01_COMMAND_W_REGISTER				0b00100000

#define NRF24L01_COMMAND_R_RX_PAYLOAD			0b01100001
#define NRF24L01_COMMAND_W_TX_PAYLOAD			0b10100000

#define NRF24L01_COMMAND_FLUSH_TX				0b11100001
#define NRF24L01_COMMAND_FLUSH_RX				0b11100010

#define NRF24L01_COMMAND_REUSE_TX_PL				0b11100011
#define NRF24L01_COMMAND_R_RX_PL_WID				0b01100000
#define NRF24L01_COMMAND_W_ACK_PAYLOAD			0b10101000
#define NRF24L01_COMMAND_W_TX_PAYLOAD_NO_ACK		0b10110000
#define NRF24L01_COMMAND_NOP						0b11111111

/*-------------------------------------*
 * NRF24L01 Registers
 *-------------------------------------*/

/* @ Register Addresses */

#define NRF24L01_REGISTER_CONFIG					0x00
#define NRF24L01_REGISTER_EN_AA					0x01
#define NRF24L01_REGISTER_EN_RXADDR				0x02
#define NRF24L01_REGISTER_SETUP_AW				0x03
#define NRF24L01_REGISTER_SETUP_RETR				0x04
#define NRF24L01_REGISTER_RF_CH					0x05
#define NRF24L01_REGISTER_RF_SETUP				0x06
#define NRF24L01_REGISTER_STATUS					0x07
#define NRF24L01_REGISTER_OBSERVE_TX				0x08
#define NRF24L01_REGISTER_RPD					0x09

#define NRF24L01_REGISTER_RX_ADDR_P0				0x0A
#define NRF24L01_REGISTER_RX_ADDR_P1				0x0B
#define NRF24L01_REGISTER_RX_ADDR_P2				0x0C
#define NRF24L01_REGISTER_RX_ADDR_P3				0x0D
#define NRF24L01_REGISTER_RX_ADDR_P4				0x0E
#define NRF24L01_REGISTER_RX_ADDR_P5				0x0F

#define NRF24L01_REGISTER_TX_ADDR				0x10

#define NRF24L01_REGISTER_RX_PW_P0				0x11
#define NRF24L01_REGISTER_RX_PW_P1				0x12
#define NRF24L01_REGISTER_RX_PW_P2				0x13
#define NRF24L01_REGISTER_RX_PW_P3				0x14
#define NRF24L01_REGISTER_RX_PW_P4				0x15
#define NRF24L01_REGISTER_RX_PW_P5				0x16

#define NRF24L01_REGISTER_FIFO_STATUS			0x17

#define NRF24L01_REGISTER_DYNDP					0x1C
#define NRF24L01_REGISTER_FEATURE				0x1D

/* @ Register Bits */

#define NRF24L01_RBIT_CONFIG_PRIM_RX				0
#define NRF24L01_RBIT_CONFIG_PWR_UP				1
#define NRF24L01_RBIT_CONFIG_CRCO				2
#define NRF24L01_RBIT_CONFIG_EN_CRC				3
#define NRF24L01_RBIT_CONFIG_MASK_MAX_RT			4
#define NRF24L01_RBIT_CONFIG_MASK_TX_DS			5
#define NRF24L01_RBIT_CONFIG_MASK_RX_DR			6

#define NRF24L01_RBIT_EN_AA_ENAA_P0				0
#define NRF24L01_RBIT_EN_AA_ENAA_P1				1
#define NRF24L01_RBIT_EN_AA_ENAA_P2				2
#define NRF24L01_RBIT_EN_AA_ENAA_P3				3
#define NRF24L01_RBIT_EN_AA_ENAA_P4				4
#define NRF24L01_RBIT_EN_AA_ENAA_P5				5

#define NRF24L01_RBIT_EN_RXADDR_ERX_P0			0
#define NRF24L01_RBIT_EN_RXADDR_ERX_P1			1
#define NRF24L01_RBIT_EN_RXADDR_ERX_P2			2
#define NRF24L01_RBIT_EN_RXADDR_ERX_P3			3
#define NRF24L01_RBIT_EN_RXADDR_ERX_P4			4
#define NRF24L01_RBIT_EN_RXADDR_ERX_P5			5

#define NRF24L01_RBIT_SETUP_AW_AW_Pos			0
#define NRF24L01_RBIT_SETUP_AW_AW(A)				(((A) & 0x3) << NRF24L01_RBIT_SETUP_AW_AW_Pos)

#define NRF24L01_RBIT_SETUP_RETR_ARDA_Pos		4
#define NRF24L01_RBIT_SETUP_RETR_ARDA(A)			(((A) & 0xF) << NRF24L01_RBIT_SETUP_RETR_ARDA_Pos)

#define NRF24L01_RBIT_SETUP_RETR_ARC_Pos			0
#define NRF24L01_RBIT_SETUP_RETR_ARC(A)			(((A) & 0xF) << NRF24L01_RBIT_SETUP_RETR_ARC_Pos)

#define NRF24L01_RBIT_RF_CH_Pos					0
#define NRF24L01_RBIT_RF_CH(A)					(((A) & 0b01111111) << NRF24L01_RBIT_RF_CH_Pos)

#define NRF24L01_RBIT_RF_PWR_pos					1
#define NRF24L01_RBIT_RF_PWR(A)					(((A) & 0x3) << NRF24L01_RBIT_RF_PWR_pos)

#define NRF24L01_RBIT_RF_SETUP_CONT_WAVE			7
#define NRF24L01_RBIT_RF_SETUP_RF_DR_LOW			5
#define NRF24L01_RBIT_RF_SETUP_PLL_LOCK			4
#define NRF24L01_RBIT_RF_SETUP_RF_DR_HIGH		3

#define NRF24L01_RBIT_RF_SETUP_RF_PWR_Pos		1
#define NRF24L01_RBIT_RF_SETUP_RF_PWR(A)			(((A) & 0x3) << NRF24L01_RBIT_RF_SETUP_RF_PWR_Pos)

#define NRF24L01_RBIT_STATUS_TX_FULL				0
#define NRF24L01_RBIT_STATUS_MAX_RT				4
#define NRF24L01_RBIT_STATUS_TX_DS				5
#define NRF24L01_RBIT_STATUS_RX_DR				6

#define NRF24L01_RBIT_STATUS_RX_P_NO_Pos			1
#define NRF24L01_RBIT_STATUS_RX_P_NO(A)			(((A) & 0x7) << NRF24L01_RBIT_RX_P_NO_Pos)

#define NRF24L01_RBIT_OBSERVE_TX_ARC_CNT_Pos		0
#define NRF24L01_RBIT_OBSERVE_TX_ARC_CNT(A)		(((A) & 0xF) << NRF24L01_RBIT_ARC_CNT_Pos)

#define NRF24L01_RBIT_OBSERVE_TX_PLOS_CNT_Pos	4
#define NRF24L01_RBIT_OBSERVE_TX_PLOS_CNT(A)		(((A) & 0xF) << NRF24L01_RBIT_PLOS_CNT_Pos)

#define NRF24L01_RBIT_RPD_RPD					0

#define NRF24L01_RBIT_RX_PW_PX_Pos
#define NRF24L01_RBIT_RX_PW_PX(A)				(((A) & 0b00111111) << NRF24L01_RBIT_RX_PW_PX_Pos)

#define NRF24L01_RBIT_FIFO_STATUS_TX_REUSE		6
#define NRF24L01_RBIT_FIFO_STATUS_TX_FULL		5
#define NRF24L01_RBIT_FIFO_STATUS_TX_EMPTY		4
#define NRF24L01_RBIT_FIFO_STATUS_RX_FULL		1
#define NRF24L01_RBIT_FIFO_STATUS_RX_EMPTY		0

#define NRF24L01_RBIT_DYNP_P0					0
#define NRF24L01_RBIT_DYNP_P1					1
#define NRF24L01_RBIT_DYNP_P2					2
#define NRF24L01_RBIT_DYNP_P3					3
#define NRF24L01_RBIT_DYNP_P4					4
#define NRF24L01_RBIT_DYNP_P5					5

#define NRF24L01_RBIT_FEATURE_EN_DPL				2
#define NRF24L01_RBIT_FEATURE_EN_ACK_PAY			1
#define NRF24L01_RBIT_FEATURE_EN_DYN_ACK			0

/*-------------------------------------*
 * NRF24L01 Prototypes
 *-------------------------------------*/

namespace Drivers::NordicSemi
{
	using namespace ::Hardware;

	typedef struct
	{
		u8			address[5];				/* The address placed in the ShockBurst packets */
		unsigned 	channel 		: 7;	/* The frequency channel */
	} NRF24L01_Config_t;

	class NRF24L01
	{
	public:
		NRF24L01(NRF24L01_Config_t config, SPI &spi, volatile GPIO_TypeDef *gpio, u8 ce) noexcept;

		/*-----------------------------*
		 * Default functions
		 *-----------------------------*/

		void init(void) noexcept;

		void transmit(u8 *address, u8 *payload, u8 plen) noexcept;

		/*-----------------------------*
		 * Register modification
		 *-----------------------------*/

		void registerWrite(u8 reg, u8 value) noexcept;
		void registerSet(u8 reg, u8 mask) noexcept;
		void registerClear(u8 reg, u8 mask) noexcept;

		u8 registerRead(u8 reg) noexcept;

		/*-----------------------------*
		 * Buffer modification
		 *-----------------------------*/

		void bufferWrite(u8 reg, u8 *data, u8 dlen) noexcept;
		void payloadWrite(u8 *data, u8 dlen) noexcept;
	private:
		NRF24L01_Config_t m_Config;
		SPI &m_SPI;
		volatile GPIO_TypeDef *m_GPIO;
		u8 m_CE;
	};
}
