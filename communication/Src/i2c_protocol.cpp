/** @file i2c_protocol.cpp
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#include <cppmain.h>
#include <i2c_protocol.h>

/***************************************************************************************************/
uint8_t i2c_tx_byte_single(I2C_HandleTypeDef hi2c, char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_I2C_Slave_Transmit(&hi2c, buf, strlen((char*)buf), HAL_MAX_DELAY);
	return 1;
}

/***************************************************************************************************/
uint8_t i2c_rx_byte_single(I2C_HandleTypeDef hi2c, uint8_t* pData)
{
	uint8_t rx_bytes = 0;

	HAL_I2C_Slave_Receive(&hi2c, pData, 1, 1);
	if( *pData == '\n')
	{
		i2c_rx_byte_single(hi2c, pData);
	}
	if ( *pData != NULL )
	{
		rx_bytes = 1;
	}
	return rx_bytes;
}
/***************************************************************************************************/
uint8_t i2c_rx_byte_multi(I2C_HandleTypeDef hi2c, uint8_t* pData, uint8_t length)
{
	uint8_t i;
	uint8_t rx_bytes = 0;

	for( i=0; i<length; i++)
	{
		rx_bytes += i2c_rx_byte_single(hi2c, pData);
		pData++;
	}
	return rx_bytes;
}
/***************************************************************************************************/
uint8_t i2c_rx_with_stop(I2C_HandleTypeDef hi2c, uint8_t* pData, char stop)
{
	uint8_t rx_bytes = 0;

	while(1)
	{
		rx_bytes += i2c_rx_byte_single(hi2c, pData);
		if( *pData == stop)
		{
			break;
		} else {
			pData++;
		}
	}

	return rx_bytes;
}
/***************************************************************************************************/
uint8_t i2c_receive(I2C_HandleTypeDef hi2c, uint8_t *pData)
{
	uint8_t rx_bytes = 0;
	uint8_t dataStarted = 0; //false
	uint8_t messageComplete = 0; //false
 	const static char startMarker = '<';
 	const static char endMarker = '>';

	while( !messageComplete )
	{
		rx_bytes += i2c_rx_byte_single(hi2c, pData);

		if( dataStarted == 1 ) //true
		{
			if( *pData != endMarker)
			{
				pData++;
			} else {
				messageComplete = 1; //true
			}

		} else if( *pData == startMarker ){
			dataStarted = 1; //true
			pData++;
		}
	}

	return rx_bytes;
}
