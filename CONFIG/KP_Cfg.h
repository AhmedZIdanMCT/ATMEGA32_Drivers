/*
 * KP_Cfg.h
 *
 *  Created on: Feb 23, 2023
 *      Author: ahmed
 */

#ifndef SRC_CONFIG_KP_CFG_H_
#define SRC_CONFIG_KP_CFG_H_
#include "DIO_Int.h"

#define NO_OF_ROWS	4
#define NO_ON_COLS	4

#define KP_ROW1	DIO_PC5
#define KP_ROW2	DIO_PC4
#define KP_ROW3	DIO_PC3
#define KP_ROW4	DIO_PC2

#define KP_COL1	DIO_PD7
#define KP_COL2	DIO_PD6
#define KP_COL3	DIO_PD5
#define KP_COL4	DIO_PD3

#define phone_keys {{'1','2','3','4'},\
					{'5','6','7','8'},\
					{'9','10','11','12'},\
					{'13','14','15','16'}}

#define calculator_keys	{{'7','8','9','/'},\
						{'4','5','6','*'},\
						{'1','2','3','-'},\
						{'0','0','=','+'}}

/*calculator_mode or phone_mode*/
#define KP_MODE	calculator_mode

#endif /* SRC_CONFIG_KP_CFG_H_ */
