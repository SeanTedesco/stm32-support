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

/*********************************************************************************
 * LOCAL VARIABLES
 */
uint8_t tx_buffer[] = "test, test, test!";
uint8_t rx_buffer[32];
uint8_t rx_byte;
uint8_t rx_flag;
uint16_t rxldx;

/*********************************************************************************
 * LOCAL FUNCTIONS
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart1, rx_buffer, 12);
}

// do stuff once
void cpp_main(){

	HAL_UART_Receive_IT(&huart1, rx_buffer, 12);

	// main loop, do stuff repeatedly
	while(1){

		print_string(huart2, "received from obc: ");
		print_string(huart2, (char*)rx_buffer);
		print_string(huart2, "\r\n");

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(250);

	}
}
