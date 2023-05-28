/*
 * TIMER_int.h
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TIMER0_TIMER_INT_H_
#define SRC_MCAL_TIMER0_TIMER_INT_H_
#include "TIMER0_cfg.h"
#include "TIMER0_priv.h"

/*this function will configure both Timer Mode and
wave Generated signal output.*/
ES_t M_TIMER_enum_Timer0_init(Timer0_cfg_type Timer0_cfg);

/*this function will starts the Timer.*/
ES_t M_TIMER_enum_Timer0_start(Timer0_cfg_type copy_cfg);

/*this function will stops the Timer.*/
ES_t M_TIMER_enum_Timer0_stop();

/*this function should return the number of counts
since timer has started .*/
ES_t M_TIMER_enum_Timer0_GetCounts(Timer0_cfg_type copy_cfg,u32* counts);

/*this function should take delay time in milli Seconds
and timer Mode , and should calculate the Number of
overflowCounts OR compareMatchCounts and/or
Preload value for ISR to work properly .*/
ES_t M_TIMER_enum_Timer0_setDelayTimeMilliSec(Timer0_cfg_type copy_cfg,u32 millisec);

/*this function should take the interrupt source ad
enables the corresponding interrupt accordingly*/
ES_t M_TIMER_enum_Timer0_EnableInt();

/*this function should take the interrupt source ad
disables the corresponding interrupt accordingly*/
ES_t M_TIMER_enum_Timer0_DisableInt();

/*this fn should set the call back pointer to a global
variable which will be used by ISR to call a higher
layer component.*/
ES_t M_TIMER_enum_Timer0_setCallBack(TIMER0_Int_type copy_Timer0_int_ID , void (*Copy_pfunAppFun)(void*),void * Copy_pvidAppParameter);

/*this fn should configure the frequency and duty to
generate a selected PWM*/
ES_t M_TIMER_enum_Timer0_setFastPWM(Timer0_cfg_type copy_cfg, f32 copy_frequency ,f32 copy_duty);

/*this fn should configure the frequency and duty to
generate a selected PWM.*/
ES_t M_TIMER_enum_Timer0_setphaseCorrectPWM(Timer0_cfg_type copy_cfg,f32 copy_frequency ,f32 copy_duty);


#endif /* SRC_MCAL_TIMER0_TIMER_INT_H_ */
