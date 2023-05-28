/*
 * Port_cfg.h
 *
 *  Created on: Feb 17, 2023
 *      Author: A.Zidan
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/******************************************
  INCLUDES
*******************************************/
#include "Std_Types.h"

/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/
#define PORT_PINS_CONFIG_ARR_SIZE 32

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/

/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/
typedef struct {
	PORT_PinType             Port_PinNumber; //PA0 or PA1...etc
	PORT_LevelType           Port_PinLevelValue;// initial value of pin
    PORT_PinDirectionType    Port_PinDirection; // input or output
	PORT_InternalAttachType  Port_PinInternalAttach;//pull up or floating

}PORT_ConfigType;

#endif /* PORT_CFG_H_ */
