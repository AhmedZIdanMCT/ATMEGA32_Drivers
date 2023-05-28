/*
 * SPI_types.h
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_SPI_SPI_TYPES_H_
#define SRC_MCAL_SPI_SPI_TYPES_H_

typedef enum{
	F_4,
	F_16,
	F_64,
	F_128,
	F_2,
	F_8,
	F_32,
	F_64_2x
}SPI_CLK_TYPE;

typedef enum {
	LEADING_SAMPLE,
	TRAILING_SAMPLE
}SPI_CLKPHASE_TYPE;

typedef enum{
	RISING_LEADING,
	FALLING_LEADING
}SPI_CLKPOLARITY_TYPE;

typedef enum{
	SLAVE,
	MASTER
}SPI_MODE_TYPE;

typedef enum{
	MSBFIRST,
	LSBFIRST
}SPI_DATAORDER_TYPE;

typedef enum{
	SPI_DISABLED,
	SPI_ENABLED
}SPI_ENABLE_TYPE;

typedef enum {
	INTERRUPT_DIS,
	INTERRUPT_ENA
}SPI_INTERRUPT_TYPE;

#endif /* SRC_MCAL_SPI_SPI_TYPES_H_ */
