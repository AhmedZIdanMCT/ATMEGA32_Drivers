/*
* Error_State.h
*
* Created: 3/18/2022 7:22:02 PM
*  Author: Ahmed
*/


#ifndef ERROR_STATE_H_
#define ERROR_STATE_H_

typedef enum
{
	ES_NOK=0,
	ES_OK=1,
	ES_OUT_OF_RANGE=2,
	ES_NULL_POINTER=3,

	/*for TWI*/
	TWI_STATUS_MASK						=0xF8,
    TWI_STATUS_START_ACK				=0x08,
    TWI_STATUS_repeated_START_ACK		=0x10,
    TWI_STATUS_SLA_ACK					=0x18,
	TWI_STATUS_SLA_R					=0x40,
    TWI_STATUS_DATA_SENT_ACK			=0x28,
    TWI_STATUS_DATA_SENT_NACK			=0x30,
	TWI_STATUS_DATA_RECEIVED_NACK		=0x58
}ES_t;



#endif /* ERROR_STATE_H_ */
