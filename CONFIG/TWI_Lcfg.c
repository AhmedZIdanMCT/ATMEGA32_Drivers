/*
 * TWI_Lcfg.c
 *
 *  Created on: Mar 9, 2023
 *      Author: ahmed
 */

#include "TWI_cfg.h"
#include "TWI_types.h"

const TWI_cfg_t TWI_cfg ={TWI_CLK16,BR_0};
const TWI_cfg_t EEPROM_TWI_cfg ={TWI_CLK1,BR_400KHZ};
