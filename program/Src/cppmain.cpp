/** @file cppmain.cpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

/*********************************************************************************
 * INCLUDES
 */
#include <cppmain.h>
#include <uart_protocol.h>
#include <i2c_protocol.h>
#include <rf24.h>

/*********************************************************************************
 * LOCAL VARIABLES
 */
uint8_t tx_buffer[] = "test, test, test!";
uint8_t rx_buffer[32];
uint8_t rx_byte;
uint8_t rx_flag;
uint16_t rxidx;

uint8_t RxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA}; // list of data pipes available
uint8_t RxData[32];
uint8_t txData[32];
uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t uButtonFlag = 0;


/*********************************************************************************
 * LOCAL FUNCTIONS
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){
		if (rx_byte == '>' || rxidx >= (32-1)) {
			rx_buffer[rxidx] = rx_byte;
			rx_flag = 1;
			rxidx = 0;
		} else {
			rx_buffer[rxidx] = rx_byte;
			rxidx++;
		}
	}
	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

uint8_t nRF24_read_regg(uint8_t Reg)
{
	uint8_t data=0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &Reg, 1, 100);
	HAL_SPI_Receive(&hspi2, &data, 1, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	return data;
}

// do stuff once
void cpp_main(){

	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);

/*
	nRF24_init();
	nRF24_rx_mode(RxAddress, 6);

	uint8_t reg_value = 0;			// initial value
	uint8_t reg_address = 5; 	//RF_CH

	reg_value = nRF24_read_regg(reg_address);

	print_string(huart2, "value: ");
	HAL_Delay(100);
	print_uint8(huart2, reg_value);
	HAL_Delay(100);
	print_string(huart2, "\r\n");
	HAL_Delay(100);
*/

	// main loop, do stuff repeatedly
	while(1){


		print_string(huart2, "received from obc: ");
		print_string(huart2, (char*)rx_buffer);
		print_string(huart2, "\r\n");

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(250);

	}
}
