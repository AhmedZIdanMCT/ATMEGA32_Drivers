/*
 * LCD_prog.c
 *
 *  Created on: Feb 19, 2023
 *      Author: ahmed
 */
#include "AVR/delay.h"
#include "LCD_priv.h"
#include "LCD_types.h"
#include "DIO_Int.h"
#include "LCD_cfg.h"

static void H_LCD_void_latchByte(u8 copy_u8Byte){

	M_DIO_void_setPinValue(LCD_RW_PIN, DIO_LOW);
	M_DIO_void_setPinValue(LCD_EN_PIN, DIO_LOW);


#if (LCD_MODE == four_bit_mode)
		M_DIO_void_setPinValue(LCD_D7_PIN,  ((copy_u8Byte>>7)&1)  );
		M_DIO_void_setPinValue(LCD_D6_PIN,  ((copy_u8Byte>>6)&1)  );
		M_DIO_void_setPinValue(LCD_D5_PIN,  ((copy_u8Byte>>5)&1)  );
		M_DIO_void_setPinValue(LCD_D4_PIN,  ((copy_u8Byte>>4)&1)  );

		M_DIO_void_setPinValue(LCD_EN_PIN, DIO_HIGH);
		_delay_ms(10);
		M_DIO_void_setPinValue(LCD_EN_PIN, DIO_LOW);
		_delay_ms(10);

		M_DIO_void_setPinValue(LCD_D7_PIN,  ((copy_u8Byte>>3)&1)  );
		M_DIO_void_setPinValue(LCD_D6_PIN,  ((copy_u8Byte>>2)&1)  );
		M_DIO_void_setPinValue(LCD_D5_PIN,  ((copy_u8Byte>>1)&1)  );
		M_DIO_void_setPinValue(LCD_D4_PIN,  ((copy_u8Byte>>0)&1)  );

		M_DIO_void_setPinValue(LCD_EN_PIN, DIO_HIGH);
		_delay_ms(10);
		M_DIO_void_setPinValue(LCD_EN_PIN, DIO_LOW);
		_delay_ms(10);

#elif(LCD_MODE == eight_bit_mode)
	M_DIO_void_setPinValue(LCD_D7_PIN,  ((copy_u8Byte>>7)&1)  );
	M_DIO_void_setPinValue(LCD_D6_PIN,  ((copy_u8Byte>>6)&1)  );
	M_DIO_void_setPinValue(LCD_D5_PIN,  ((copy_u8Byte>>5)&1)  );
	M_DIO_void_setPinValue(LCD_D4_PIN,  ((copy_u8Byte>>4)&1)  );
	M_DIO_void_setPinValue(LCD_D3_PIN,  ((copy_u8Byte>>3)&1)  );
	M_DIO_void_setPinVaylue(LCD_D2_PIN,  ((copy_u8Byte>>2)&1)  );
	M_DIO_void_setPinValue(LCD_D1_PIN,  ((copy_u8Byte>>1)&1)  );
	M_DIO_void_setPinValue(LCD_D0_PIN,  ((copy_u8Byte>>0)&1)  );

	M_DIO_void_setPinValue(LCD_EN_PIN, DIO_HIGH);
	_delay_ms(10);
	M_DIO_void_setPinValue(LCD_EN_PIN, DIO_LOW);
	_delay_ms(10);

#else
	#error "LCD Mode Configuration is wrong\n it must be EIGHT_BIT or FOUR_BIT"
#endif
}

void H_LCD_void_sendCommand(u8 copy_u8command){
	M_DIO_void_setPinValue(LCD_RS_PIN,DIO_LOW);
	H_LCD_void_latchByte(copy_u8command);
}

void H_LCD_void_sendData(u8 copy_u8data ){
	M_DIO_void_setPinValue(LCD_RS_PIN,DIO_HIGH);
	H_LCD_void_latchByte(copy_u8data);
}

void H_LCD_void_Init(void){

	_delay_ms(35);
	M_DIO_void_setPinValue(LCD_RS_PIN,DIO_LOW);
	M_DIO_void_setPinValue(LCD_D7_PIN,DIO_LOW);
	M_DIO_void_setPinValue(LCD_D6_PIN,DIO_LOW);
	M_DIO_void_setPinValue(LCD_D5_PIN,DIO_HIGH);
	M_DIO_void_setPinValue(LCD_D4_PIN,DIO_LOW);

	M_DIO_void_setPinValue(LCD_EN_PIN, DIO_HIGH);
	_delay_ms(10);
	M_DIO_void_setPinValue(LCD_EN_PIN, DIO_LOW);
	_delay_ms(10);

	H_LCD_void_sendCommand(LCD_Fun_set);

	H_LCD_void_sendCommand(0x0f);

	H_LCD_void_sendCommand(0x01);

	H_LCD_void_sendCommand(0x06);
}

void H_LCD_void_sendIntNum(u32 copy_s32Num){
	int i = -1;
	u8 digits[4];

	if(copy_s32Num == 0){
		H_LCD_void_sendData('0');
	}

	if(copy_s32Num <0){
		H_LCD_void_sendData('-');
		copy_s32Num *= -1;
	}

	while(copy_s32Num){
	i++;
	digits[i] = (copy_s32Num % 10)+'0';
	copy_s32Num /= 10;
	}
	for(int j=i;j>=0;j--){
		H_LCD_void_sendData(digits[j]);
	}
}

void H_LCD_void_sendString(const u8 * pstr){
	if(pstr!=NULL){
		while(*pstr){
			H_LCD_void_sendData(*pstr++);
		}
	}
	else{

	}
}

void H_LCD_void_gotoXY(u8 copy_u8Row,u8 copy_u8Col){
	if(copy_u8Row<=2 &&copy_u8Row>0 &&copy_u8Col<=20 && copy_u8Col>0){
		H_LCD_void_sendCommand(0x80 + (copy_u8Row-1) + (copy_u8Col-1)*0x14);
	}
}

void H_LCD_void_creatCustomChar(const u8 * ArrPattern,u8 copy_u8charCode){
	H_LCD_void_sendCommand(LCD_CGRAM_addr + (copy_u8charCode<<3));
	for(int i=0;i<8;i++){
		H_LCD_void_sendData(ArrPattern[i]);
	}
	H_LCD_void_sendCommand(LCD_DDRAM_addr+ + copy_u8charCode);

}

void H_LCD_void_displayCustomChar(u8 copy_u8charCode){
	H_LCD_void_sendData(copy_u8charCode);
}

