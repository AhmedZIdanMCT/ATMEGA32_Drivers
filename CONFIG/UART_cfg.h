/*
 * UART_cfg.h
 *
 *  Created on: Mar 4, 2023
 *      Author: ahmed
 */

#ifndef SRC_CONFIG_UART_CFG_H_
#define SRC_CONFIG_UART_CFG_H_
#include "UART_types.h"

#define Freq	16000000UL

typedef struct{
	UART_MODE_t synchronization_mode;
	UART_Bauderate_t baudrate;
	UART_Word_Length_t wordLength;
	UART_Parity_t barityBits;
	UART_Stop_Bits_t stopBits;
}UART_cfg_t;


#endif /* SRC_CONFIG_UART_CFG_H_ */
