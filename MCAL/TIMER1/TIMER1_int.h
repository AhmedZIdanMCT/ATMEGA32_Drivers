/*
 * TIMER1_int.h
 *
 *  Created on: Feb 26, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TIMER1_TIMER1_INT_H_
#define SRC_MCAL_TIMER1_TIMER1_INT_H_
#include "Error_State.h"
#include "TIMER1_Types.h"

ES_t M_TIMER1_enu_init();
ES_t M_TIMER1_enu_start();
ES_t M_TIMER1_enu_ICU_IntEnable();
ES_t M_TIMER1_enu_ICU_IntDisable();
ES_t M_TIMER1_enu_ICU_void_setTrigg(TIMER1_Edge_type copy_edge_type);
ES_t M_TIMER1_ICU_clearTimer();
ES_t M_TIMER1_enu_ICU_takeReading(u16* reading);
//this function returns the value of Input capture register
ES_t M_TIMER1_ICU_setCallBack(TIMER1_Int_type copy_Timer1_int_ID, ES_t (*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter);

#endif /* SRC_MCAL_TIMER1_TIMER1_INT_H_ */
