/*
 * UART_int.h
 *
 *  Created on: Mar 4, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_UART_UART_INT_H_
#define SRC_MCAL_UART_UART_INT_H_
#include "UART_cfg.h"
ES_t UART_Init(UART_cfg_t copy_cfg);
ES_t UART_Send_Word(UART_cfg_t copy_cfg,u8 copy_data);
ES_t UART_Send_String(UART_cfg_t copy_cfg, char* string);
ES_t UART_receiveByteSynchNonBlocking(UART_cfg_t copy_cfg, u8* copy_recieved_data);
ES_t UART_receiveByteAsynchCallBack( u8* copy_recieved_data);
ES_t UART_Callback(void (*pAppFun)(void*),void * pAppParameter);

#endif /* SRC_MCAL_UART_UART_INT_H_ */
