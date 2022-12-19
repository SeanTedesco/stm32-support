/** @file i2c_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#ifndef UART_PROTOCOL_H_
#define UART_PROTOCOL_H_

class Serial {
	public: // attributes
		uint16_t rxidx = 0;
		uint8_t rx_flag = 0;
		uint8_t rx_buffer[32];
		uint8_t rx_byte;

	public: // methods
		void print_string(UART_HandleTypeDef huart, char* string);
		void print_uint8(UART_HandleTypeDef huart, uint8_t number);
};

#endif /* UART_PROTOCOL_H_ */
