/*
 * TIMER1_prg.c
 *
 *  Created on: Feb 26, 2023
 *      Author: ahmed
 */
#include "STD_TYPES.h"
#include "Error_State.h"
#include "Mcu_HW.h"
#include <avr/interrupt.h>
#include "TIMER1_Priv.h"
#include "TIMER1_int.h"

static ES_t (* TIMER1_ApfunISRFun[4])()={NULL,NULL,NULL,NULL};
static void * TIMER1_ApvidISRParameter [4] ={NULL,NULL,NULL,NULL};
u16 TIMER1_ICR_readings[]={0};
u8 i =0;

/*to be extended after configuration management*/
ES_t M_TIMER1_enu_init(){
	ES_t Local_enuErrorState = ES_OK;
	//determine Normal WGM
	TCCR1A &= T1_clr_WGM10;
	TCCR1A |= T1_Normal_WGM10;
	TCCR1B &= T1_clr_WGM32;
	TCCR1B |= T1_Normal_WGM32;

	//on compare match Set OCPA
	TCCR1A &= T1_clr_COMA;
	TCCR1A |= T1_Set_Set_Set_COMA;
	TCCR1B &= T1_clr_COMB;

	//enable OF interrupt
	TIMSKR &= T1_clr_TOIE;
	TIMSKR |= T1_En_TOIE;

	//enable OCA interrupt
	TIMSKR &= T1_clr_OCIEA;
	TIMSKR |= T1_En_OCIEA;
	return Local_enuErrorState;
}

ES_t M_TIMER1_enu_start(){
	ES_t Local_enuErrorState =ES_OK;
	//set prescaler to 1
	TCCR1B &= T1_clr_CS;
	TCCR1B |= T1_Clc_CS;
	return Local_enuErrorState;
}


ES_t M_TIMER1_enu_ICU_IntEnable(){
	ES_t Local_enuErrorState = ES_OK;
	TIMSKR &= T1_clr_TICE;
	TIMSKR |= T1_En_TICE;
	return Local_enuErrorState;
}

ES_t M_TIMER1_enu_ICU_IntDisable(){
	ES_t Local_enuErrorState = ES_OK;
	TIMSKR &= T1_clr_TICE;
	TIMSKR &= ~(T1_En_TICE);
	return Local_enuErrorState;
}

ES_t M_TIMER1_enu_ICU_void_setTrigg(TIMER1_Edge_type copy_edge_type){
	ES_t Local_enuErrorState = ES_OK;
	TCCR1B &= T1_clr_ICES;
	switch(copy_edge_type){
	case rising_edge:
		TCCR1B |= T1_RE_ICES;
		break;
	case falling_edge:
		TCCR1B &= ~(T1_RE_ICES);
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ES_t M_TIMER1_enu_ICU_takeReading(u16* reading){
	ES_t Local_enuErrorState = ES_OK;
	*reading = ICR1L;
	return Local_enuErrorState;
}

ES_t M_TIMER1_ICU_clearTimer(){
	ES_t Local_enuErrorState=ES_OK;
	TCNT1H = 0;
	return Local_enuErrorState;
}
ES_t M_TIMER1_ICU_setCallBack(TIMER1_Int_type copy_Timer1_int_ID, ES_t (*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter){
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_pfunAppFun != NULL){
		if(copy_Timer1_int_ID <=1){
		TIMER1_ApfunISRFun[copy_Timer1_int_ID  ] = Copy_pfunAppFun;
		TIMER1_ApvidISRParameter[ copy_Timer1_int_ID ] = Copy_pvidAppParameter;
		Local_enuErrorState = ES_OK;
		}
		else{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}

ISR(TIMER1_CAPT_vect){

	/*if(i==0){
		//detect rising edge
		TCCR1B &= T1_clr_ICES;
		TCCR1B |= T1_RE_ICES;
		//clear ICF
		TIFR &= ~(T1_set_ICF);
		//buffer the reading
		M_TIMER1_enu_ICU_takeReading(&TIMER1_ICR_readings[0]);
		i=1;
	}
	if(i==1){
		//detect falling edge
		TCCR1B &= T1_clr_ICES;
		TCCR1B &= ~(T1_RE_ICES);
		//clear ICF
		TIFR &= ~(T1_set_ICF);
		i=0;
	}*/
	if (TIMER1_ApfunISRFun[TIMER1_IC_int] != NULL){
		TIMER1_ApfunISRFun[TIMER1_IC_int](TIMER1_ApvidISRParameter[ TIMER1_IC_int]);
	}
}

