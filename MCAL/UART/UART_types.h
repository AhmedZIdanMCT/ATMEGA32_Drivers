/*
 * UART_types.h
 *
 *  Created on: Mar 4, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_UART_UART_TYPES_H_
#define SRC_MCAL_UART_UART_TYPES_H_
typedef enum{
	baudrate_9600 = 103,
	baudrate_115200 = 8

}UART_Bauderate_t;

typedef enum
{
	Asynchronous=0,
	Synchronous
}UART_MODE_t;

typedef enum
{
	Disable=0,
	Even=2,
	Odd=3
}UART_Parity_t;

typedef enum
{
	One_bit=0,
	Two_bit=1
}UART_Stop_Bits_t;

typedef enum
{
	Five_bit=0,
	Six_bit=1,
	Seven_bit=2,
	Eight_bit=3,
	Nine_bit=7
}UART_Word_Length_t;

typedef enum
{
	Transmit_Rising_Receive_Falling=0,
	Transmit_Falling_Receive_Rising=1
}UART_CLK_Polarity_t;

#endif /* SRC_MCAL_UART_UART_TYPES_H_ */
