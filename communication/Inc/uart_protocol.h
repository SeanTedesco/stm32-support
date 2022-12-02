/** @file i2c_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#ifndef UART_PROTOCOL_H_
#define UART_PROTOCOL_H_

/***************************************************************************************************
 * @brief:
 * @param:
 * @return:
 */
uint8_t print_string(UART_HandleTypeDef huart, char* string);


/***************************************************************************************************/
/*
 * @brief:
 * @param:
 * @return:
 */
uint8_t uart_rx_byte_single(UART_HandleTypeDef huart, uint8_t* buffer);

#endif /* UART_PROTOCOL_H_ */
