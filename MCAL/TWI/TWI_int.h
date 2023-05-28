/*
 * TWI_int.h
 *
 *  Created on: Mar 9, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TWI_TWI_INT_H_
#define SRC_MCAL_TWI_TWI_INT_H_

ES_t M_TWI_enu_Init(TWI_cfg_t Copy_TWI_cfg);
ES_t M_TWI_enu_SetSlaveAddress(u8 Copy_SlaveAddress);
ES_t M_TWI_enu_SendStart();
ES_t M_TWI_enu_SendByte(u8 Copy_DataByte);
ES_t M_TWI_enu_RecevieByteACK(u8 *ptr_received_data);
ES_t M_TWI_enu_RecevieByteNACK(u8 *ptr_received_data);
ES_t M_TWI_enu_GetStatus();
ES_t M_TWI_enu_SendStop();


 typedef enum{
	  TWI_INIT_MASK					=0x84,
	  TWI_START_MASK				=0xA4,
	  TWI_SEND_BYTE_MASK			=0x84,
	  TWI_RECEIVE_WITH_ACK_MASK		=0xC4,
	  TWI_RECEIVE_WITH_NACK_MASK	=0x84,
	  TWI_STOP_MASK					=0x94,

 }TWI_masks;





#endif /* SRC_MCAL_TWI_TWI_INT_H_ */
