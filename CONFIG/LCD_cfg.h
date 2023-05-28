/*
 * LCD_cfg.h
 *
 *  Created on: Feb 19, 2023
 *      Author: ahmed
 */

#ifndef SRC_CONFIG_LCD_CFG_H_
#define SRC_CONFIG_LCD_CFG_H_
#include "DIO_Types.h"
#include "LCD_types.h"

#define LCD_RW_PIN	DIO_PA4
#define LCD_EN_PIN	DIO_PA2
#define LCD_RS_PIN	DIO_PA3
#define LCD_D0_PIN	DIO_PB5
#define LCD_D1_PIN	DIO_PB6
#define LCD_D2_PIN	DIO_PB7
#define LCD_D3_PIN	DIO_PB3
#define LCD_D4_PIN	DIO_PB0
#define LCD_D5_PIN	DIO_PB1
#define LCD_D6_PIN	DIO_PB2
#define LCD_D7_PIN	DIO_PB4

#define eight_bit_mode	0x10
#define four_bit_mode	0x00

#define LCD_MODE	four_bit_mode


#endif /* SRC_CONFIG_LCD_CFG_H_ */
