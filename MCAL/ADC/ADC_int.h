/*
 * ADC_int.h
 *
 *  Created on: Mar 3, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_ADC_ADC_INT_H_
#define SRC_MCAL_ADC_ADC_INT_H_

#include "Error_State.h"
#include "ADC_cfg.h"
#include "STD_TYPES.h"

ES_t M_ADC_enu_init(ADC_cfg_type copy_ADCcfg);
ES_t M_ADC_enu_getDigitalValueSynchNonBlocking(ADC_cfg_type* copy_ADCcfg, float* voltage);
ES_t M_ADC_enu_getDigitalValueAsynchCallBack( float* voltage);
ES_t M_ADC_enu_setCallBack(ES_t (*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter);
ES_t M_ADC_enu_startConversion();

#endif /* SRC_MCAL_ADC_ADC_INT_H_ */
