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
uint8_t RxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA}; // list of data pipes available
uint8_t RxData[32];
uint8_t txData[32];
uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};

/*********************************************************************************
 * LOCAL FUNCTIONS
 */


// do stuff once
void cpp_main(){

	Serial transmitter(huart2);							// transmit on huart2
	HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1);	// receive on huart1

	// main loop, do stuff repeatedly
	while(1){

		if (uart1_rx_flag == 1){
			uart1_rx_flag = 0;
			transmitter.print_string("received from obc: ");
			transmitter.print_string((char*)uart1_rx_buffer);
			transmitter.print_string("\r\n");
		}

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(250);
	}
}
