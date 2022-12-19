/** @file i2c_protocol.h
 *
 * @author	sean-tedesco
 * @date	2022-11-29
 */

#ifndef UART_PROTOCOL_H_
#define UART_PROTOCOL_H_

#define max_rx_buffer_size 128

extern uint8_t uart1_rx_buffer[max_rx_buffer_size];
extern uint8_t uart1_rx_byte;
extern uint8_t uart1_rx_flag;

extern uint8_t uart2_rx_buffer[max_rx_buffer_size];
extern uint8_t uart2_rx_byte;
extern uint8_t uart2_rx_flag;

class Serial {
	public: // attributes
		UART_HandleTypeDef internal_huart;

	public: // methods
		Serial(UART_HandleTypeDef huart);
		void print_string(char* string);
		void print_uint8(uint8_t number);
};

#endif /* UART_PROTOCOL_H_ */
