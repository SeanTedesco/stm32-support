/** @file i2c_protocol.hpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#include <cppmain.h>
#include <uart_protocol.h>
#include "string.h"
#include <stdio.h>

/****************************************************************************************************/
void Serial::print_this(UART_HandleTypeDef huart, char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
void Serial::print_uint8(UART_HandleTypeDef huart, uint8_t number)
{
	uint8_t buf[4];
	sprintf((char*)buf, "%d", number);
	HAL_UART_Transmit(&huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
	return 1;
}

/****************************************************************************************************/
