/*
 * SPI_cfg.h
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */

#ifndef SRC_CONFG_SPI_CFG_H_
#define SRC_CONFG_SPI_CFG_H_

#include "SPI_types.h"
typedef struct{
	SPI_MODE_TYPE SPI_mode;
	SPI_CLKPHASE_TYPE SPI_phase;
	SPI_CLKPOLARITY_TYPE SPI_polarity;
	SPI_DATAORDER_TYPE SPI_dataOrder;
	SPI_INTERRUPT_TYPE SPI_interrupt;
	SPI_CLK_TYPE SPI_clk;
	SPI_ENABLE_TYPE SPI_en_dis;
}SPI_CFG_TYPE;

#endif /* SRC_CONFG_SPI_CFG_H_ */
