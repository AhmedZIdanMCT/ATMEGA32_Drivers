/*
 * SSD_prg.c
 *
 *  Created on: Feb 18, 2023
 *      Author: ahmed
 */
#include "STD_TYPES.h"
#include "AVR/delay.h"
#include "Mcu_HW.h"
#include "BIT_MATH.h"
#include "Dio_int.h"
#include "SSD_priv.h"
#include "SSD_types.h"
#include "SSD_int.h"
#include "SSD_cfg.h"

void H_SSD_VOID_displayNumber(u16 copy_Number){
	u8 arr[4]={0};
	u8 i =0;
	/*separate digits*/
	while(copy_Number>0 && i<4){
		arr[i]= copy_Number%10;
		copy_Number/=10;
		i++;
	}


	for(int j;j<SSD_DISPLAY_TIME;j++){
	i=0;
	//prepare units to be sent to BCD (4 bits)
	M_DIO_void_setPinValue(SSD_A_PIN, (arr[i]>>0)&	1 );
	M_DIO_void_setPinValue(SSD_B_PIN, (arr[i]>>1)&	1 );
	M_DIO_void_setPinValue(SSD_C_PIN, (arr[i]>>2)&	1 );
	M_DIO_void_setPinValue(SSD_D_PIN, (arr[i]>>3)&	1 );

	//Enable digit 1 (remember it is pnp and active low)
	M_DIO_void_setPinValue(SSD_DIG1_EN_PIN, DIO_LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(SSD_DIG1_EN_PIN, DIO_HIGH);

	//tens
	i=1;
	M_DIO_void_setPinValue(SSD_A_PIN, (arr[i]>>0)&	1 );
	M_DIO_void_setPinValue(SSD_B_PIN, (arr[i]>>1)&	1 );
	M_DIO_void_setPinValue(SSD_C_PIN, (arr[i]>>2)&	1 );
	M_DIO_void_setPinValue(SSD_D_PIN, (arr[i]>>3)&	1 );
	//Enable digit 1 (remember it is pnp and active low)
	M_DIO_void_setPinValue(SSD_DIG2_EN_PIN, DIO_LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(SSD_DIG2_EN_PIN, DIO_HIGH);

	//hundreds
	i=2;
	M_DIO_void_setPinValue(SSD_A_PIN, (arr[i]>>0)&	1 );
	M_DIO_void_setPinValue(SSD_B_PIN, (arr[i]>>1)&	1 );
	M_DIO_void_setPinValue(SSD_C_PIN, (arr[i]>>2)&	1 );
	M_DIO_void_setPinValue(SSD_D_PIN, (arr[i]>>3)&	1 );
	//Enable digit 1 (remember it is pnp and active low)
	M_DIO_void_setPinValue(SSD_DIG3_EN_PIN, DIO_LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(SSD_DIG3_EN_PIN, DIO_HIGH);

	//thousands
	i=3;
	M_DIO_void_setPinValue(SSD_A_PIN, (arr[i]>>0)&	1 );
	M_DIO_void_setPinValue(SSD_B_PIN, (arr[i]>>1)&	1 );
	M_DIO_void_setPinValue(SSD_C_PIN, (arr[i]>>2)&	1 );
	M_DIO_void_setPinValue(SSD_D_PIN, (arr[i]>>3)&	1 );
	//Enable digit 1 (remember it is pnp and active low)
	M_DIO_void_setPinValue(SSD_DIG4_EN_PIN, DIO_LOW);
	_delay_ms(1);
	M_DIO_void_setPinValue(SSD_DIG4_EN_PIN, DIO_HIGH);
	}


}

