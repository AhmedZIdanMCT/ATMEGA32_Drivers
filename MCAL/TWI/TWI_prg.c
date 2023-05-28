/*
 * TWI_prg.c
 *
 *  Created on: Mar 9, 2023
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "Error_State.h"
#include "BIT_MATH.h"
#include "avr/io.h"
#include "DIO_Int.h"
#include "TWI_types.h"
#include "TWI_priv.h"
#include "TWI_cfg.h"
#include "TWI_int.h"


ES_t M_TWI_enu_Init(TWI_cfg_t Copy_TWI_cfg){
	ES_t Local_enuErrorState = ES_NOK;
	/*prescaler*/
	TWI_PRESCALLER_t twi_pres = Copy_TWI_cfg.prescaler;
	switch (twi_pres){
	case TWI_CLK1:
		TWSR_PTR->TWPS_BITS=Copy_TWI_cfg.prescaler;
		Local_enuErrorState = ES_OK;
		break;
	case TWI_CLK4:
		TWSR_PTR->TWPS_BITS=Copy_TWI_cfg.prescaler;
		Local_enuErrorState = ES_OK;
		break;
	case TWI_CLK16:
		TWSR_PTR->TWPS_BITS=Copy_TWI_cfg.prescaler;
		Local_enuErrorState = ES_OK;
		break;
	case TWI_CLK64:
		TWSR_PTR->TWPS_BITS=Copy_TWI_cfg.prescaler;
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	/*bitrate*/
	TWI_BITRATE_t twi_bitrate = Copy_TWI_cfg.bitrate;
	switch(twi_bitrate){
		case BR_0:
			TWI_TWBR = Copy_TWI_cfg.bitrate;
			Local_enuErrorState = ES_OK;
			break;
		case BR_100KHZ:
			TWI_TWBR = Copy_TWI_cfg.bitrate;
			Local_enuErrorState = ES_OK;
			break;
		case BR_400KHZ:
			TWI_TWBR = Copy_TWI_cfg.bitrate;
			Local_enuErrorState = ES_OK;
			break;
		default :
			Local_enuErrorState = ES_OUT_OF_RANGE;

	}
	/*enable TWI*/
	TWI_TWCR |= TWI_INIT_MASK ;

	return Local_enuErrorState;
}

ES_t M_TWI_enu_SendStart(){
	ES_t Local_enuErrorState = ES_OK;
	//TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	TWI_TWCR |= TWI_START_MASK ;
	/* wait for transmission complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)) == 0);

	return Local_enuErrorState;

}

ES_t M_TWI_enu_GetStatus(){
	ES_t Local_enuErrorState = ES_OK;
	Local_enuErrorState= (TWI_TWSR & TWI_STATUS_MASK);

	return Local_enuErrorState;
}

ES_t M_TWI_enu_SendByte(u8 Copy_DataByte){
	ES_t Local_enuErrorState = ES_OK;
	/* Transmit data to TWDR*/
	TWI_TWDR = Copy_DataByte ;
	/*clear start bit*/
	TWI_TWCR &= (~TWI_CLR_START_BIT);
	/* Clear interrupt flag To initiate transmission*/
	TWI_TWCR |= TWI_SEND_BYTE_MASK;
	/* Wait till data transmitted */
	while ((GET_BIT(TWI_TWCR,TWCR_TWINT)) == 0);

	return Local_enuErrorState;
}

ES_t M_TWI_enu_RecevieByteACK(u8 *ptr_received_data){
	ES_t Local_enuErrorState = ES_OK;
	/* Clear interrupt flag To initiate initiate transmission*/
	TWI_TWCR = TWI_RECEIVE_WITH_ACK_MASK;
	/* Wait till data transmitted */
	while (!(TWI_TWCR & (1<<TWCR_TWINT)));
	/*return data*/
	*ptr_received_data = TWI_TWDR ;

	return Local_enuErrorState;
}



ES_t M_TWI_enu_RecevieByteNACK(u8 *ptr_received_data){
	ES_t Local_enuErrorState = ES_OK;
	M_DIO_void_setPinValue(DIO_PC0, DIO_HIGH);
	/* Clear interrupt flag To initiate transmission*/
	TWI_TWCR = TWI_RECEIVE_WITH_NACK_MASK;
	/* Wait till data transmitted */
	while (!(TWI_TWCR & (1<<TWCR_TWINT)));
	/*return data*/
	*ptr_received_data = TWI_TWDR ;

	return Local_enuErrorState;
}


ES_t M_TWI_enu_SendStop(){
	ES_t Local_enuErrorState = ES_OK;
	/*send stop condition*/
	TWI_TWCR |= TWI_STOP_MASK ;

	return Local_enuErrorState;

}

ES_t M_TWI_enu_SetSlaveAddress(u8 Copy_SlaveAddress){
	ES_t Local_enuErrorState = ES_OK;
	TWI_TWAR = Copy_SlaveAddress ;

	return Local_enuErrorState;

}

