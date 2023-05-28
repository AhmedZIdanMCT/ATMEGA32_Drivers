/*
 * EEPROM_prg.c
 *
 *  Created on: Mar 10, 2023
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "Error_State.h"
#include <avr/io.h>
#include "LCD_int.h"
#include "TWI_cfg.h"
#include "TWI_int.h"

#define EEPROM_SLA_W	0xA0
#define EEPROM_SLA_R	0xA1
#define adress_mask 	0x0300 //anding with adress and shift right 7 times
ES_t H_EEPROM_enu_init(TWI_cfg_t copy_EEPROM_cfg){
	ES_t Local_enuErrorState = ES_OK;
	M_TWI_enu_Init(copy_EEPROM_cfg);
	return Local_enuErrorState;
}


ES_t H_EEPROM_enu_writeByte(u16 copy_byteAdress, u8 copy_byteData){
	ES_t Local_enuErrorState = ES_NOK;

	M_TWI_enu_SendStart();/*send start*/
	/*get start status*/
	Local_enuErrorState = M_TWI_enu_GetStatus();

	if(Local_enuErrorState == TWI_STATUS_START_ACK){
		M_TWI_enu_SendByte(EEPROM_SLA_W | (copy_byteAdress & adress_mask)>>7 );/*send sla+w+A9+A8*/
		/*get status*/
		Local_enuErrorState = M_TWI_enu_GetStatus();

		if(Local_enuErrorState == TWI_STATUS_SLA_ACK){
			M_TWI_enu_SendByte((u8)copy_byteAdress);	/*send A7->A0*/
			/*get status*/
			Local_enuErrorState = M_TWI_enu_GetStatus();

			if(Local_enuErrorState == TWI_STATUS_DATA_SENT_ACK){
				M_TWI_enu_SendByte(copy_byteData);	/*send data byte*/
				/*get status*/
				Local_enuErrorState = M_TWI_enu_GetStatus();

				if(Local_enuErrorState == TWI_STATUS_DATA_SENT_ACK){
					M_TWI_enu_SendStop();	/*send stop condition*/
					Local_enuErrorState = ES_OK;	/*writing complete*/
				}
			}
		}
	}

	return Local_enuErrorState;
}

ES_t H_EEPROM_enu_readByte(u16 copy_byteAdress , u8* copy_data_received){
	ES_t Local_enuErrorState = ES_NOK;

		M_TWI_enu_SendStart();/*send start*/
		/*get start status*/
		Local_enuErrorState = M_TWI_enu_GetStatus();

		if(Local_enuErrorState == TWI_STATUS_START_ACK){
			M_TWI_enu_SendByte(EEPROM_SLA_W | (copy_byteAdress & adress_mask)>>7 );/*send sla+w+A9+A8*/
			/*get status*/
			Local_enuErrorState = M_TWI_enu_GetStatus();

			if(Local_enuErrorState == TWI_STATUS_SLA_ACK){
				M_TWI_enu_SendByte((u8)copy_byteAdress);	/*send A7->A0*/
				/*get status*/
				Local_enuErrorState = M_TWI_enu_GetStatus();

				if(Local_enuErrorState == TWI_STATUS_DATA_SENT_ACK){
					M_TWI_enu_SendStart();		/*send repeated start*/
					/*get status*/
					Local_enuErrorState = M_TWI_enu_GetStatus();

					if(Local_enuErrorState == TWI_STATUS_repeated_START_ACK){
						M_TWI_enu_SendByte(EEPROM_SLA_R);	/*send SLA+R*/
						/*get status*/
						Local_enuErrorState = M_TWI_enu_GetStatus();

						if(Local_enuErrorState == TWI_STATUS_SLA_R){
							M_TWI_enu_RecevieByteNACK(copy_data_received);	/*read data byte*/
							/*get status*/
							Local_enuErrorState = M_TWI_enu_GetStatus();

							if(Local_enuErrorState == TWI_STATUS_DATA_RECEIVED_NACK){
								M_TWI_enu_SendStop();		/*send stop condition*/
								Local_enuErrorState = ES_OK;	/*receive complete*/
							}
						}
					}
				}
			}
		}

		return Local_enuErrorState;
}

