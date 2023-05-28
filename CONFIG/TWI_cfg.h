/*
 * TWI_cfg.h
 *
 *  Created on: Mar 9, 2023
 *      Author: ahmed
 */

#ifndef SRC_CONFIG_TWI_CFG_H_
#define SRC_CONFIG_TWI_CFG_H_

#include "TWI_types.h"

typedef struct{
	TWI_PRESCALLER_t prescaler;
	TWI_BITRATE_t bitrate;
}TWI_cfg_t;


#endif /* SRC_CONFIG_TWI_CFG_H_ */
