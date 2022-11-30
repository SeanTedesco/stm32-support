/** @file cppmain.cpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#include "cppmain.h"
#include "i2c_protocol.hpp"

int some_variable = 0;

void foo(int input){
  // do something
}


void cpp_main(){
	// do stuff once
	uint8_t msg_buffer[24];

	// main loop
	while(1){
		// do stuff repeatedly

	  strcpy((char*)msg_buffer, "Hello QSET\r\n");
	  HAL_UART_Transmit(&huart2, msg_buffer, strlen((char*)msg_buffer), 100);

	  strcpy((char*)msg_buffer, "Hello OBC\r\n");
	  HAL_UART_Transmit(&huart1, msg_buffer, strlen((char*)msg_buffer), 100);

	  HAL_Delay(1000);

	}
}
