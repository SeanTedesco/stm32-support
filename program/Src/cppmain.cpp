/** @file cppmain.cpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#include <cppmain.h>
#include <uart_protocol.h>


int some_variable = 0;

void foo(int input){
  // do something
}


void cpp_main(){
	// do stuff once

	//uint8_t buffer[32];
	uint8_t obc_buffer[32];

	// main loop
	while(1){
		// do stuff repeatedly

		print_string(huart1, "hello obc!!\r\n");

		uart_rx_byte_singlestring(huart1, obc_buffer);

		print_string(huart2, "received from obc: ");
		print_string(huart2, (char*)obc_buffer);
		print_string(huart2, "\r\n");

		HAL_Delay(1000);

	}
}
