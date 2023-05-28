/*
 * SPI_Lcfg.c
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */

#include "SPI_types.h"
#include "SPI_cfg.h"

const SPI_CFG_TYPE SPI_cfg[2] ={
		{
				MASTER,
				LEADING_SAMPLE,
				FALLING_LEADING,
				MSBFIRST,
				INTERRUPT_DIS,
				F_4,
				SPI_ENABLED

		},
		{
				SLAVE,
				LEADING_SAMPLE,
				FALLING_LEADING,
				MSBFIRST,
				INTERRUPT_DIS,
				F_4,
				SPI_ENABLED
		}
};
