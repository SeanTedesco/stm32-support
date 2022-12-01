/** @file i2c_protocol.hpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#include <cppmain.h>
#include <uart_protocol.h>

/****************************************************************************************************/
uint8_t print_string(UART_HandleTypeDef huart ,char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
	return 1;
}

/****************************************************************************************************/
uint8_t receive_string(uint8_t* buffer)
{
	return 1;
}


