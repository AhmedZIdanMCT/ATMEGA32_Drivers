/*
 * TWI_priv.h
 *
 *  Created on: Mar 9, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TWI_TWI_PRIV_H_
#define SRC_MCAL_TWI_TWI_PRIV_H_

#define TWI_CLR_PRESCALLER			0xF8
#define TWI_CLR_START_BIT			0x20


typedef struct{
	volatile u8	TWPS_BITS	:2;
	volatile u8				:1;
	volatile u8	TWS_BITS	:5;
}TWSR_BF;

volatile static TWSR_BF* TWSR_PTR = ((volatile TWSR_BF*)0x21);

typedef struct{
	volatile u8	TWIE_BITS	:1;
	volatile u8				:1;
	volatile u8	TWEN_BITS	:1;
	volatile u8	TWWC_BITS	:1;
	volatile u8	TWSTO_BITS	:1;
	volatile u8	TWSTA_BITS	:1;
	volatile u8	TWEA_BITS	:1;
	volatile u8	TWINT_BITS	:1;
}TWCR_BF;

volatile static TWCR_BF* TWCR_PTR = ((volatile TWCR_BF*)0x56);

#define TWI_TWAR		(*((volatile u8*)0x22))
#define TWI_TWDR		(*((volatile u8*)0x23))
#define TWI_TWSR		(*((volatile u8*)0x21))
#define TWI_TWCR		(*((volatile u8*)0x56))
#define TWI_TWBR		(*((volatile u8*)0x20))
#define TWCR_TWINT			7
#endif /* SRC_MCAL_TWI_TWI_PRIV_H_ */
