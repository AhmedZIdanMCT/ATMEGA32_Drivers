/*
 * EEPROM_int.h
 *
 *  Created on: Mar 10, 2023
 *      Author: ahmed
 */

#ifndef SRC_HAL_EEPROM_EEPROM_INT_H_
#define SRC_HAL_EEPROM_EEPROM_INT_H_

#include "TWI_types.h"
#include "TWI_cfg.h"
#include "Error_State.h"

ES_t H_EEPROM_enu_init(TWI_cfg_t copy_EEPROM_cfg);
ES_t H_EEPROM_enu_writeByte(u8 copy_byteAdress, u8 copy_byteData);
ES_t H_EEPROM_enu_readByte(u8 copy_byteAdress, u8* copy_byteData);

#endif /* SRC_HAL_EEPROM_EEPROM_INT_H_ */
