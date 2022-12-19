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
uint16_t rxidx = 0;
uint8_t rx_flag = 0;
uint8_t rx_buffer[32];
uint8_t rx_byte;

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

// do stuff once
void cpp_main(){

	Serial myserial;

	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);

	// main loop, do stuff repeatedly
	while(1){

		myserial.print_string(huart2, "received from obc: ");
		myserial.print_string(huart2, (char*)rx_buffer);
		myserial.print_string(huart2, "\r\n");

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(250);

	}
}
