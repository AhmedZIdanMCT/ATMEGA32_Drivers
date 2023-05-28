/*
 * UART_prg.c
 *
 *  Created on: Mar 4, 2023
 *      Author: ahmed
 */
#include "Error_State.h"
#include "STD_TYPES.h"
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "UART_priv.h"
#include "UART_cfg.h"
#include "UART_int.h"

void (*pAppFun)(void*);
void * pAppParameter;

ES_t UART_Init(UART_cfg_t copy_cfg){
	ES_t Local_enuErrorState = ES_NOK;

	/*enable TX*/
	UCSRB_ptr->TXEN_bits = 1;

	/*enable RX*/
	UCSRB_ptr->RXEN_bits = 1;

	/*baudRate*/
	UBRRLreg = 51;
	UBRRH_ptr->UBRR_bits=(51>>8);
	/*Synchronization mode*/
	UART_MODE_t synchronization_mode = copy_cfg.synchronization_mode;
	switch (synchronization_mode){
	case Asynchronous:
		UCSRC &= UMSEL_clr;
		UCSRC |= UMSEL_ASYN_mask;
		//clear polarity bit
		UCSRC &= clr_UCPOL;
		UCSRC |= UCPOL_Transmit_Rising_Receive_Falling_mask;
		Local_enuErrorState = ES_OK;
		break;
	case Synchronous:
		UCSRC &= UMSEL_clr;
		UCSRC |= UMSEL_SYN_mask;
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}


	/*set word length*/
	UART_Word_Length_t wordLength = copy_cfg.wordLength;
	switch (wordLength){
	case Five_bit:
		UCSRB_ptr->UCSZ2_bits=0;
		UCSRC &= clr_UCSZ;
		UCSRC |= UCSZ_5_bit_mask;
		Local_enuErrorState = ES_OK;
		break;
	case Six_bit:
		UCSRB_ptr->UCSZ2_bits=0;
		UCSRC &= clr_UCSZ;
		UCSRC |= UCSZ_6_bit_mask;
		Local_enuErrorState = ES_OK;
			break;
	case Seven_bit:
		UCSRB_ptr->UCSZ2_bits=0;
		UCSRC &= clr_UCSZ;
		UCSRC |= UCSZ_7_bit_mask;
		Local_enuErrorState = ES_OK;
			break;
	case Eight_bit:
		UCSRB_ptr->UCSZ2_bits=0;
		UCSRC &= clr_UCSZ;
		UCSRC |= UCSZ_8_bit_mask;
		Local_enuErrorState = ES_OK;
			break;
	case Nine_bit:
		UCSRB_ptr->UCSZ2_bits=1;
		UCSRC &= clr_UCSZ;
		UCSRC |= UCSZ_9_bit_mask;
		Local_enuErrorState = ES_OK;
			break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	//set parity mode
	UART_Parity_t parityMode = copy_cfg.barityBits;
	switch (parityMode){
	case Disable:
		UCSRC &= UPM_clr;
		UCSRC |= UPM_disable;
		Local_enuErrorState = ES_OK;
		break;
	case Even:
		UCSRC &= UPM_clr;
		UCSRC |= UPM_even;
		Local_enuErrorState = ES_OK;
		break;
	case Odd:
		UCSRC &= UPM_clr;
		UCSRC |= UPM_odd;
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	//set stop bits
	UART_Stop_Bits_t stopMode = copy_cfg.stopBits;
	switch(stopMode){
	case One_bit:
		UCSRC &= USBS_clr;
		UCSRC |= USBS_1_bit;
		Local_enuErrorState = ES_OK;
		break;
	case Two_bit:
		UCSRC &= USBS_clr;
		UCSRC |= USBS_2_bit;
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	/*enable receive interrupt
	UCSRB_ptr->RXCIE_bits=1;*/

	return Local_enuErrorState;
}

ES_t UART_Send_Word(UART_cfg_t copy_cfg,u8 copy_data){
	ES_t Local_enuErrorState = ES_OK;
	while(UCSRA_ptr->UDRE_bits==0){}
	if(copy_cfg.wordLength==Nine_bit){
		UCSRB_ptr->TXB8_bits = (copy_data>>7);
		UDR=copy_data;
	}
	else{
		UDR=copy_data;
	}


	return Local_enuErrorState;
}

ES_t UART_Send_String(UART_cfg_t copy_cfg, char* string){
	ES_t Local_enuErrorState = ES_OK;
	u8 i=0;
	while(string[i]!='\0'){
		while(UCSRA_ptr->UDRE_bits==0){}
			if(copy_cfg.wordLength==Nine_bit){
					UCSRB_ptr->TXB8_bits = (string[i]>>7);
					UDR=string[i];
			}
			else{
					UDR=string[i];
			}
			_delay_ms(30);
			i++;
	}
	while(UCSRA_ptr->UDRE_bits==0){}
	UDR = '\0';
	return Local_enuErrorState;
}

ES_t UART_receiveByteSynchNonBlocking(UART_cfg_t copy_cfg, u8* copy_recieved_data){
	ES_t Local_enuErrorState = ES_OK;
	while(UCSRA_ptr->RXC_bits==0);
	if(copy_cfg.wordLength==Nine_bit){
			UCSRB_ptr->RXB8_bits = (*copy_recieved_data>>7);
			*copy_recieved_data = UDR;
		}
		else{
			*copy_recieved_data = UDR;
		}
	return Local_enuErrorState;
}

ES_t UART_receiveByteAsynchCallBack( u8* copy_recieved_data){
	ES_t Local_enuErrorState = ES_OK;
	if(UCSRB_ptr->UCSZ2_bits==1){
				UCSRB_ptr->RXB8_bits = (*copy_recieved_data>>7);
				*copy_recieved_data = UDR;
			}
			else{
				*copy_recieved_data = UDR;
			}
	return Local_enuErrorState;
}

ES_t UART_Callback(void (*copy_pAppFun)(void*),void * copy_pAppParameter){
	ES_t Local_enuErrorState = ES_NOK;
	if(copy_pAppFun != NULL){
		pAppFun=copy_pAppFun;
		pAppParameter=copy_pAppParameter;
		Local_enuErrorState = ES_OK;
	}
	else {
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ISR(USART_RXC_vect){
	if(pAppFun != NULL){
		pAppFun(pAppParameter);
	}
}
