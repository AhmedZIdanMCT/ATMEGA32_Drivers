/*
n  * LCD_priv.h
 *
 *  Created on: Feb 19, 2023
 *      Author: ahmed
 */

#ifndef SRC_HAL_LCD_LCD_PRIV_H_
#define SRC_HAL_LCD_LCD_PRIV_H_
#include "STD_TYPES.h"

/*instructions*/

#define LCD_CLEAR_DISPLAY				0x01
#define LCD_RETURN_HOME					0x02
#define LCD_ENTRY_MODE					0x04
#define LCD_DISPLAY_ON_OFF				0x08
#define LCD_cursor_Disp_shift			0x10
#define LCD_Fun_set						0x20
#define LCD_CGRAM_addr					0x40
#define LCD_DDRAM_addr					0x80


static void H_LCD_void_latchByte(u8 copy_u8Byte);




#endif /* SRC_HAL_LCD_LCD_PRIV_H_ */


