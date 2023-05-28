/*
 * prg.c
 *
 *  Created on: Feb 23, 2023
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "AVR\delay.h"
#include "DIO_Int.h"
#include "KP_Int.h"
#include "KP_Cfg.h"

u8 H_KEYPAD_u8_getPressedKey(void){
	u8 copy_u8Keyvalue=0;
	DIO_LevelType signal=0;
	u8 flag=0;
	int r=0;
	int c=0;
	DIO_ChannelType rows[] = {KP_ROW1 , KP_ROW2 , KP_ROW3 , KP_ROW4};
	DIO_ChannelType cols[] = {KP_COL1 , KP_COL2 ,KP_COL3 , KP_COL4};
	for(r=0;r<NO_OF_ROWS;r++){
		M_DIO_void_setPinValue(rows[r],DIO_LOW);
		for(c=0;c<NO_ON_COLS;c++){
			signal =M_DIO_enu_getPinValue(cols[c]);
			if(!signal){
				_delay_ms(10);
				signal = M_DIO_enu_getPinValue(cols[c]);
				if(!signal){
					while(!signal){
						signal = M_DIO_enu_getPinValue(cols[c]);
						#if (KP_MODE == calculator_mode )
							u8 localU8KeyValues[NO_OF_ROWS][NO_ON_COLS] = calculator_keys;
						#elif (KP_MODE == phone_mode)
							u8 localU8KeyValues[NO_OF_ROWS][NO_ON_COLS] = phone_keys;
						#else
							#error "wrong KP_mode"
						#endif
						copy_u8Keyvalue = localU8KeyValues[r][c];
						flag = 1;
					}
				}
			}
		}
		M_DIO_void_setPinValue(rows[r],DIO_HIGH);
	}
if(!flag){
	copy_u8Keyvalue = 0xff;
}
return copy_u8Keyvalue;
}
