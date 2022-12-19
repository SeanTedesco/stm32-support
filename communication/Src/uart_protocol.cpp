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
Serial::Serial(UART_HandleTypeDef huart)
{
	internal_huart = huart;
}

/****************************************************************************************************/
void Serial::print_string( char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&internal_huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
void Serial::print_uint8(uint8_t number)
{
	uint8_t buf[4];
	sprintf((char*)buf, "%d", number);
	HAL_UART_Transmit(&internal_huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

/****************************************************************************************************/
