/*
 * UART_priv.h
 *
 *  Created on: Mar 4, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_UART_UART_PRIV_H_
#define SRC_MCAL_UART_UART_PRIV_H_


typedef struct{
	volatile u8 MPCM_bits	:1;
	volatile u8 U2X_bits	:1;
	volatile u8 PE_bits   	:1;
	volatile u8 DOR_bits    :1;
	volatile u8 FE_bits   	:1;
	volatile u8 UDRE_bits   :1;
	volatile u8 TXC_bits   	:1;
	volatile u8 RXC_bits   	:1;
}UCSRA_BF;
static volatile UCSRA_BF* UCSRA_ptr	=(volatile UCSRA_BF*)(0x2B);

typedef struct{
	volatile u8 TXB8_bits	 :1;
	volatile u8 RXB8_bits	 :1;
	volatile u8 UCSZ2_bits   :1;
	volatile u8 TXEN_bits    :1;
	volatile u8 RXEN_bits    :1;
	volatile u8 UDRIE_bits   :1;
	volatile u8 TXCIE_bits   :1;
	volatile u8 RXCIE_bits   :1;
}UCSRB_BF;
static volatile UCSRB_BF* UCSRB_ptr = (volatile UCSRB_BF*)(0x2A);

typedef struct{
	volatile u8 UCPOL_bits	:1;
	volatile u8 UCSZ_bits	:2;
	volatile u8 USBS_bits	:1;
	volatile u8 UPM_bits  	:2;
	volatile u8 UMSEL_bits	:1;
	volatile u8 URSEL_bits 	:1;
}UCSRC_BF;
static volatile UCSRC_BF* UCSRC_ptr = (volatile UCSRC_BF*)(0x40);

#define clr_UCPOL									0xFE
#define UCPOL_Transmit_Rising_Receive_Falling_mask	0x80
#define UCPOL_Transmit_Falling_Receive_Rising_mask	0x81
#define clr_UCSZ									0xF9
#define UCSZ_5_bit_mask								0x80
#define UCSZ_6_bit_mask								0x82
#define UCSZ_7_bit_mask								0x84
#define UCSZ_8_bit_mask								0x86
#define UCSZ_9_bit_mask								0x86 // remember the 3rd bit
#define USBS_clr									0xF7
#define USBS_1_bit									0x80
#define USBS_2_bit									0x88
#define UPM_clr										0xCF
#define UPM_disable									0x80
#define UPM_even									0xA0
#define UPM_odd										0xB0
#define UMSEL_clr									0xBF
#define UMSEL_ASYN_mask								0x80
#define UMSEL_SYN_mask								0xC0



typedef struct{
	volatile u8 UBRR_bits	:4;
	volatile u8				:3;
	volatile u8 URSEL_bits 	:1;
}UBRRH_BF;
static volatile UBRRH_BF* UBRRH_ptr	= (volatile UBRRH_BF*)(0x40);

#define UBRRLreg			(*(volatile u8*)(0x29))
#endif /* SRC_MCAL_UART_UART_PRIV_H_ */
