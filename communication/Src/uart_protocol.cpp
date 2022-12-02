/** @file i2c_protocol.hpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#include <cppmain.h>
#include <uart_protocol.h>

/****************************************************************************************************/
uint8_t print_string(UART_HandleTypeDef huart, char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&huart, buf, strlen((char*)buf), HAL_MAX_DELAY);
	return 1;
}

/****************************************************************************************************/
uint8_t uart_rx_byte_single(UART_HandleTypeDef huart, uint8_t* buffer)
{
	uint8_t rx_bytes = 0;

	HAL_UART_Receive(&huart, buffer, 1, 0.5);
	if( *buffer == '\n')
	{
		uart_rx_byte_single(huart, buffer);
	}
	if ( *buffer != NULL )
	{
		rx_bytes++;
	}
	return rx_bytes;

}


