/*
 * SPI_priv.h
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_SPI_SPI_PRIV_H_
#define SRC_MCAL_SPI_SPI_PRIV_H_

typedef struct {
	volatile u8 SPR_bits	:2;
	volatile u8 SPHA_bits	:1;
	volatile u8 CPOL_bits	:1;
	volatile u8 MSTR_bits	:1;
	volatile u8 DORD_bits	:1;
	volatile u8 SPE_bits	:1;
	volatile u8 SPIE_bits	:1;
}SPCR_BF;

volatile static SPCR_BF* SPCR_PTR = ((volatile SPCR_BF*) 0x2D);

typedef struct {
	volatile u8 SPI2X_bits	:1;
	volatile u8				:5;
	volatile u8 WCOL_bits	:1;
	volatile u8 SPIF_bits	:1;
}SPSR_BF;

volatile SPSR_BF* SPSR_PTR = ((volatile SPSR_BF*)0x2E);
#define SPI_SPDR_reg		   	(*((volatile u8*)0x2F));

#endif /* SRC_MCAL_SPI_SPI_PRIV_H_ */
