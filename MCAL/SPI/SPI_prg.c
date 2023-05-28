/*
 * SPI_prg.c
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */

#include "Mcu_HW.h"
#include "avr/io.h"
#include <avr/delay.h>
#include "avr/interrupt.h"
#include "STD_TYPES.h"
#include "Error_State.h"
#include "DIO_Int.h"
#include "SPI_priv.h"
#include "SPI_types.h"
#include "SPI_cfg.h"
#include "SPI_int.h"

void(*pfunAppFun)(void*) = NULL;
void * pvidAppParameter = NULL;

ES_t M_SPI_enu_init(SPI_CFG_TYPE copy_SPI_cfg){
	ES_t Local_enuErrorState = ES_OK;
	/*Selecting mode (master/slave)*/
	switch (copy_SPI_cfg.SPI_mode){
	case MASTER:
		SPCR_PTR->MSTR_bits =copy_SPI_cfg.SPI_mode;
		/*configure MOSI,CLK,SS to output and pull SS down*/
		M_Dio_void_setPinDirection(DIO_PB5, DIO_output);
		M_Dio_void_setPinDirection(DIO_PB7, DIO_output);
		M_Dio_void_setPinDirection(DIO_PB4, DIO_output);
		M_DIO_void_setPinValue(DIO_PB4,DIO_LOW);
		break;
	case SLAVE:
		SPCR_PTR->MSTR_bits =copy_SPI_cfg.SPI_mode;
		/*configure MISO to be output*/
		M_Dio_void_setPinDirection(DIO_PB6, DIO_output);
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;

	}
	/*Selecting phase (leading sample/ trailing sample)*/
	if(copy_SPI_cfg.SPI_phase == LEADING_SAMPLE || copy_SPI_cfg.SPI_phase == TRAILING_SAMPLE){
		SPCR_PTR->SPHA_bits =copy_SPI_cfg.SPI_phase;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	/*Selecting polarity (Rising Leading / falling leading)*/
	if(copy_SPI_cfg.SPI_polarity == RISING_LEADING || copy_SPI_cfg.SPI_polarity == FALLING_LEADING){
		SPCR_PTR->CPOL_bits = copy_SPI_cfg.SPI_polarity;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	/*Selecting data order (MSB 1st /LSB 1st)*/
	if(copy_SPI_cfg.SPI_dataOrder == MSBFIRST || copy_SPI_cfg.SPI_dataOrder == LSBFIRST){
		SPCR_PTR->DORD_bits = copy_SPI_cfg.SPI_dataOrder;
	}
	else {
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	/*Interrupt state (interrupt disabled / interrupt enabled)*/
	if(copy_SPI_cfg.SPI_interrupt == INTERRUPT_ENA || copy_SPI_cfg.SPI_interrupt== INTERRUPT_DIS){
		SPCR_PTR->SPIE_bits = copy_SPI_cfg.SPI_interrupt;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	/*determine clock rate*/
	SPI_CLK_TYPE SPI_clock = copy_SPI_cfg.SPI_clk;
	switch (SPI_clock){
	case F_4:
		SPCR_PTR->SPR_bits = 0;
		Local_enuErrorState = ES_OK;
		break;
	case F_16:
		SPCR_PTR->SPR_bits = 1;
		Local_enuErrorState = ES_OK;
		break;
	case F_64:
		SPCR_PTR->SPR_bits = 2;
		Local_enuErrorState = ES_OK;
		break;
	case F_128:
		SPCR_PTR->SPR_bits = 3;
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	/*enable or disable*/
	if(copy_SPI_cfg.SPI_en_dis == SPI_ENABLED || copy_SPI_cfg.SPI_en_dis == SPI_DISABLED){
		SPCR_PTR->SPE_bits = copy_SPI_cfg.SPI_en_dis;
		Local_enuErrorState = ES_OK;
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ES_t M_SPI_enu_transferByteSynch(u8* copy_transmit_data,u8* copy_receive_data){
	ES_t Local_enuErrorState = ES_NOK;
	/*transmit data*/
	 SPDR = *copy_transmit_data;
	 /*wait for transmission complete*/
	 while(!(SPSR_PTR->SPIF_bits));
	 /*receive data*/
	 *copy_receive_data = SPDR;
	 return Local_enuErrorState;
}

ES_t M_SPI_enu_transferString(u8* copy_transmit_data){
	ES_t Local_enuErrorState= ES_OK;
	u8 read_data;
	while(*copy_transmit_data != '\0'){
		/*transmit data*/
		SPDR =*copy_transmit_data;
		/* Wait for transmission complete */
		while(!(SPSR & (1<<7)));
		/* read data */
		read_data = SPDR;
		_delay_ms(30);
		copy_transmit_data++;

	}
	SPDR = '\0';
	return	Local_enuErrorState;
}

ES_t M_SPI_enu_receiveByteSynch(u8* copy_receive_data){
	ES_t Local_enuErrorState = ES_NOK;
	/*send dummy value*/
	SPDR =0x00;
	/*wait for transmission complete*/
	while(/*!(SPSR_PTR->SPIF_bits)*/!(SPSR & (1<<7)));
	/*receive data*/
	*copy_receive_data = SPDR;
	return Local_enuErrorState;
}

ES_t M_SPI_enu_receiveByteAsynchCallBack(u8* copy_receive_data){
	ES_t Local_enuErrorState = ES_OK;
	/*receive data*/
	*copy_receive_data = SPDR;
	return Local_enuErrorState;
}

ES_t M_SPI_enum_setCallBack(void(*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pfunAppFun != NULL){
		pfunAppFun = Copy_pfunAppFun;
		pvidAppParameter = Copy_pvidAppParameter;
		Local_enuErrorState = ES_OK;
	}
	else{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}

ISR(SPI_STC_vect)
{
	if(pfunAppFun != NULL)
	{
		pfunAppFun(pvidAppParameter);
	}

}
