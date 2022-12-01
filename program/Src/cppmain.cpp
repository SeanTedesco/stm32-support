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

	// main loop
	while(1){
		// do stuff repeatedly

		print_string(huart2, "hello qset!!\r\n");

		print_string(huart1, "hello obc!!\r\n");

		HAL_Delay(1000);

	}
}
