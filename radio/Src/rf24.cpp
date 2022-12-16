/** @file rf24.cpp
 *
 * @author	sean-tedesco
 * @date	2022-12-15
 */

/***************************************************************************************************
 * INCLUDES
 *
 */
#include "cppmain.h"
#include "rf24.h"
#include "uart_protocol.h"

/***************************************************************************************************
 * DEFINES
 *
 */
#define nRF24_SPI &hspi3
// Define the Chip-Enable GPIO address
#define nRF24_CE_PORT   GPIOC
#define nRF24_CE_PIN    GPIO_PIN_6

// Define the Chip-Select GPIO address.
#define nRF24_CSN_PORT   GPIOB
#define nRF24_CSN_PIN    GPIO_PIN_12

/***************************************************************************************************
 * FUNCTIONS
 *
 */

/* @brief: calling this will pull CS low (desired for starting SPI transaction).
 * @param: void
 * @return: void
 */
void CS_Select(void)
{
	HAL_GPIO_WritePin(nRF24_CSN_PORT, nRF24_CSN_PIN, GPIO_PIN_RESET);
}

/* @brief: calling this will set CS high (desired for ending SPI transaction).
 * @param: void
 * @return: void
 */
void CS_UnSelect(void)
{
	HAL_GPIO_WritePin(nRF24_CSN_PORT, nRF24_CSN_PIN, GPIO_PIN_SET);
}

/* @brief: calling this will pull CE high (desired for starting communication transaction).
 * @param: void
 * @return: void
 */
void CE_Enable(void)
{
	HAL_GPIO_WritePin(nRF24_CE_PORT, nRF24_CE_PIN, GPIO_PIN_SET);
}

/* @brief: calling this will pull CE low (desired for starting communication transaction).
 * @param: void
 * @return: void
 */
void CE_Disable(void)
{
	HAL_GPIO_WritePin(nRF24_CE_PORT, nRF24_CE_PIN, GPIO_PIN_RESET);
}

/* @brief: write a single byte to the particular register
 * @param: address: the address (register) to write the data
 * @param: data:	the data to be written
 * @return: void
 */
void nRF24_write_reg (uint8_t address, uint8_t data)
{
	uint8_t buf[2];
	buf[0] = address|1<<5;
	buf[1] = data;

	CS_Select();
	HAL_SPI_Transmit(nRF24_SPI, buf, 2, 1000);
	CS_UnSelect();
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_write_reg_multi(uint8_t Reg, uint8_t *data, int size)
{
	uint8_t buf[2];
	buf[0] = Reg|1<<5;
	//buf[1] = Data;

	CS_Select();
	HAL_SPI_Transmit(nRF24_SPI, buf, 1, 100);
	HAL_SPI_Transmit(nRF24_SPI, data, size, 1000);
	CS_UnSelect();
}

/* @brief:
 * @param:
 * @return:
 */
uint8_t nRF24_read_reg (uint8_t Reg)
{
	uint8_t data=0;

	CS_Select();
	HAL_SPI_Transmit(nRF24_SPI, &Reg, 1, 100);
	HAL_SPI_Receive(nRF24_SPI, &data, 1, 100);
	CS_UnSelect();
	return data;
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_read_reg_multi(uint8_t Reg, uint8_t *data, int size)
{
	CS_Select();
	HAL_SPI_Transmit(nRF24_SPI, &Reg, 1, 100);
	HAL_SPI_Receive(nRF24_SPI, data, size, 1000);
	CS_UnSelect();
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_send_cmd(uint8_t cmd)
{
	CS_Select();
	HAL_SPI_Transmit(nRF24_SPI, &cmd, 1, 100);
	CS_UnSelect();
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_reset(uint8_t REG)
{
	print_string(huart2, "begin reset...\r\n");
	if (REG == NRF_STATUS){
		nRF24_write_reg(NRF_STATUS, 0x00);

	} else if (REG == FIFO_STATUS){
		nRF24_write_reg(FIFO_STATUS, 0x11);

	} else {
		nRF24_write_reg(NRF_CONFIG, 0x08);
		nRF24_write_reg(EN_AA, 0x3F);
		nRF24_write_reg(EN_RXADDR, 0x03);
		nRF24_write_reg(SETUP_AW, 0x03);
		nRF24_write_reg(SETUP_RETR, 0x03);
		nRF24_write_reg(RF_CH, 0x02);
		nRF24_write_reg(RF_SETUP, 0x0E);
		nRF24_write_reg(NRF_STATUS, 0x00);
		nRF24_write_reg(OBSERVE_TX, 0x00);
		nRF24_write_reg(CD, 0x00);

		uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nRF24_write_reg_multi(RX_ADDR_P0, rx_addr_p0_def, 5);
		uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
		nRF24_write_reg_multi(RX_ADDR_P1, rx_addr_p1_def, 5);
		nRF24_write_reg(RX_ADDR_P2, 0xC3);
		nRF24_write_reg(RX_ADDR_P3, 0xC4);
		nRF24_write_reg(RX_ADDR_P4, 0xC5);
		nRF24_write_reg(RX_ADDR_P5, 0xC6);
		uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nRF24_write_reg_multi(TX_ADDR, tx_addr_def, 5);
		nRF24_write_reg(RX_PW_P0, 0);
		nRF24_write_reg(RX_PW_P1, 0);
		nRF24_write_reg(RX_PW_P2, 0);
		nRF24_write_reg(RX_PW_P3, 0);
		nRF24_write_reg(RX_PW_P4, 0);
		nRF24_write_reg(RX_PW_P5, 0);
		nRF24_write_reg(FIFO_STATUS, 0x11);
		nRF24_write_reg(DYNPD, 0);
		nRF24_write_reg(FEATURE, 0);
	}
	print_string(huart2, "end reset...\r\n");
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_init(void)
{
	print_string(huart2, "begin init...\r\n");
	CE_Disable();
	nRF24_reset(0);
	nRF24_write_reg(NRF_CONFIG, 0);
	nRF24_write_reg(EN_AA, 0);
	nRF24_write_reg(EN_RXADDR, 0);
	nRF24_write_reg(SETUP_AW, 0x03);
	nRF24_write_reg(SETUP_RETR, 0);
	nRF24_write_reg(RF_CH, 0);
	nRF24_write_reg(RF_SETUP, 0x0E);
	CE_Enable();
	print_string(huart2, "end init...\r\n");
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_tx_mode(uint8_t *address, uint8_t channel)
{
	CE_Disable();
	nRF24_write_reg(RF_CH, channel);
	nRF24_write_reg_multi(TX_ADDR, address, 5);
	uint8_t config = nRF24_read_reg(NRF_CONFIG);
	config = config & (0xF2);
	nRF24_write_reg(NRF_CONFIG, config);
	CE_Enable();
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_rx_mode(uint8_t *address, uint8_t channel)
{
	CE_Disable();
	nRF24_reset(NRF_STATUS);
	nRF24_write_reg(RF_CH, channel);

	uint8_t en_rxaddr = nRF24_read_reg(EN_RXADDR);
	en_rxaddr = en_rxaddr | (1<<2);
	nRF24_write_reg(EN_RXADDR, en_rxaddr);
	nRF24_write_reg_multi(RX_ADDR_P1, address, 5);
	nRF24_write_reg(RX_ADDR_P2, 0xEE);
	nRF24_write_reg(RX_PW_P2, 32);
	uint8_t config = nRF24_read_reg(NRF_CONFIG);
	config = config | (1<<1) | (1<<0);
	nRF24_write_reg(NRF_CONFIG, config);
	CE_Enable();
}

/* @brief:
 * @param:
 * @return:
 */
uint8_t nRF24_transmit (uint8_t *data)
{
	uint8_t cmdtosend = 0;
	CS_Select();
	cmdtosend = W_TX_PAYLOAD;
	HAL_SPI_Transmit(nRF24_SPI, &cmdtosend, 1, 100);
	HAL_SPI_Transmit(nRF24_SPI, data, 32, 1000);
	CS_UnSelect();
	HAL_Delay(1);
	uint8_t fifostatus = nRF24_read_reg(FIFO_STATUS);
	if ((fifostatus&(1<<4)) && (!(fifostatus&(1<<3))))
	{
		cmdtosend = FLUSH_TX;
		nRF24_send_cmd(cmdtosend);
		nRF24_reset(FIFO_STATUS);
		return 1;
	}
	return 0;
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_receive (uint8_t *data)
{
	uint8_t cmdtosend = 0;
	CS_Select();
	cmdtosend = R_RX_PAYLOAD;
	HAL_SPI_Transmit(nRF24_SPI, &cmdtosend, 1, 100);
	HAL_SPI_Receive(nRF24_SPI, data, 32, 1000);
	CS_UnSelect();
	HAL_Delay(1);
	cmdtosend = FLUSH_RX;
	nRF24_send_cmd(cmdtosend);
}

/* @brief:
 * @param:
 * @return:
 */
uint8_t nRF24_is_data_available(int pipenum)
{
	uint8_t status = nRF24_read_reg(NRF_STATUS);
	if ((status&(1<<6))&&(status&(pipenum<<1)))
	{
		nRF24_write_reg(NRF_STATUS, (1<<6));
		return 1;
	}
	return 0;
}

/* @brief:
 * @param:
 * @return:
 */
void nRF24_read_all (uint8_t *data)
{
	for (int i=0; i<10; i++)
	{
		*(data+i) = nRF24_read_reg(i);
	}

	nRF24_read_reg_multi(RX_ADDR_P0, (data+10), 5);

	nRF24_read_reg_multi(RX_ADDR_P1, (data+15), 5);

	*(data+20) = nRF24_read_reg(RX_ADDR_P2);
	*(data+21) = nRF24_read_reg(RX_ADDR_P3);
	*(data+22) = nRF24_read_reg(RX_ADDR_P4);
	*(data+23) = nRF24_read_reg(RX_ADDR_P5);

	nRF24_read_reg_multi(RX_ADDR_P0, (data+24), 5);

	for (int i=29; i<38; i++)
	{
		*(data+i) = nRF24_read_reg(i-12);
	}

}

