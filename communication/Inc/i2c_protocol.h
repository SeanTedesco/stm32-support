/** @file i2c_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#ifndef COMMUNICATION_INC_I2C_PROTOCOL_H_
#define COMMUNICATION_INC_I2C_PROTOCOL_H_

/*
 * @brief: receive one byte from the I2C bus acting as a slave
 * 			will try again if the new-line character is received.
 * 			This makes what is being received more intuitive and
 * 			tapping enter does not break up any of the data.
 * @param: pData - the pointer to store the data received from
 * 			the I2C bus
 * @return: rx_bytes - returns 1 if successfully received a byte,
 * 			otherwise will return 0.
 */
static uint8_t i2c_rx_byte_single(uint8_t* pData);

/***************************************************************************************************/
/*
 * @brief: receive a number of bytes equal to the value of /p length
 * 			from the I2C bus acting as a slave. Calls i2c_rx_byte_single.
 * @param: pData - the pointer to store the data received from
 * 			the I2C bus
 * @param: length - the number of bytes to be received.
 * @return: rx_bytes - the total number of bytes successfully received.
 */
static uint8_t i2c_rx_byte_multi(uint8_t* pData, uint8_t length);

/***************************************************************************************************/
/*
 * @brief: receive bytes from the I2C bus until the /p stop condition is
 * 			received.
 * @param: pData - the pointer to store the data received from
 * 			the I2C bus
 * @param: stop - the character that will arrest the reception of data.
 * @return: rx_bytes - the total number of bytes successfully received.
 */
static uint8_t i2c_rx_with_stop(uint8_t* pData, char stop);

/***************************************************************************************************/
/*
 * @brief: receive bytes from the I2C bus that are enclosed by the
 * 			start '<' and stop '>' characters.
 * @param: pData - the pointer to store the data received from
 * 			the I2C bus.
 * @return: rx_bytes - the total number of bytes successfully received.
 */
static uint8_t i2c_receive(uint8_t *pData);

#endif /* COMMUNICATION_INC_I2C_PROTOCOL_H_ */
