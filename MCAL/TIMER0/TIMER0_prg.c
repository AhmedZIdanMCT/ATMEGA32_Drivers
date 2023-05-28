/*
 * TIMER0_prg.c
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmed
 */

#include "Mcu_HW.h"
#include "STD_TYPES.h"
#include "Error_State.h"
#include <avr/interrupt.h>
#include "TIMER0_priv.h"
#include "TIMER_types.h"
#include "TIMER_int.h"
extern Timer0_cfg_type timer0_cfg1;

static  u32 No_Of_overFlows =0;
static u32 Local_no_of_overflows =0;
static  u32 No_Of_compareMatches =0;
static u32 local_no_of_compareMAtches=0;

static void (* TIMER0_ApfunISRFun[2])()={NULL,NULL};
static void * TIMER0_ApvidISRParameter [2] ={NULL,NULL};

ES_t M_TIMER_enum_Timer0_init(Timer0_cfg_type copy_Timer0_cfg){
ES_t Local_enuErrorState = ES_NOK;
switch (copy_Timer0_cfg.WG_mode){
	case Normal:
		TCCR0 &= clr_WGM;
		TCCR0 |= Normal_WGM;
		Local_enuErrorState = ES_OK;
		break;
	case PhaseCorrect_PWM:
		TCCR0 &= clr_WGM;
		TCCR0 |= PWM_PC_WGM;
		Local_enuErrorState = ES_OK;
		break;
	case CTC:
		TCCR0 &= clr_WGM;
		TCCR0 |= CTC_WGM;
		Local_enuErrorState = ES_OK;
		break;
	case Fast_PWM:
		TCCR0 &= clr_WGM;
		TCCR0 |= PWM_FAST_WGM;
		Local_enuErrorState = ES_OK;
		break;
	default:
		Local_enuErrorState = ES_NOK;
		return Local_enuErrorState;
}

switch (copy_Timer0_cfg.CO_mode){
	case Disconnected:
		TCCR0 &= clr_COM;
		TCCR0 |= Dis_Dis_COM;
		break;
	case Toogle:
		TCCR0 &= clr_COM;
		TCCR0 |= Tog_Res_COM;
		break;
	case Clear:
		TCCR0 &= clr_COM;
		TCCR0 |= Clr_Clr_COM;
		break;
	case Set:
		TCCR0 &= clr_COM;
		TCCR0 |= Set_Set_COM;
		break;
	default:
		Local_enuErrorState = ES_NOK;
		return Local_enuErrorState;
}

switch (copy_Timer0_cfg.OF_intterrupt_mode){
	case OFI_Disabled:
		TIMSKR  &= clr_TOIE;
		TIMSKR &= ~(En_TOIE) ;
		break;
	case OFI_Enabled:
		TIMSKR &= clr_TOIE;
		TIMSKR |= En_TOIE;
		break;
	default:
		Local_enuErrorState = ES_NOK;
		return Local_enuErrorState;
}

switch (copy_Timer0_cfg.OC_intterrupt_mode){
	case OCI_Disabled:
		TIMSKR  &= clr_OCIE;
		TIMSKR &= ~(En_OCIE) ;
		break;
	case OCI_Enabled:
		TIMSKR &= clr_OCIE;
		TIMSKR |= En_OCIE;
		break;
	default:
		Local_enuErrorState = ES_NOK;
		return Local_enuErrorState;
}
return Local_enuErrorState;
}

ES_t M_TIMER_enum_Timer0_start(Timer0_cfg_type copy_cfg){
ES_t Local_enuErrorState = ES_NOK;
OCR0 = copy_cfg.OCR;
switch (copy_cfg.clk_source){
case IO_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Clc_CS;
	break;
case IO_8PS_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Clc_8PS_CS;
	break;
case IO_64PS_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Clc_64PS_CS;
	break;
case IO_256PS_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Clc_256PS_CS;
	break;
case IO_1024_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Clc_1024PS_CS;
	break;
case EXT_Falling_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Ext_Falling_CS;
	break;
case EXT_Rising_clk:
	TCCR0 &= clr_CS;
	TCCR0 |= Ext_Rising_CS;
	break;
default:
	Local_enuErrorState = ES_NOK;
	break;
}
return Local_enuErrorState;
}

ES_t M_TIMER_enum_Timer0_stop(){
ES_t Local_enu_ErrorState = ES_OK;
TCCR0 &= clr_CS;
TCCR0 |= NO_clc_CS;
return Local_enu_ErrorState;
}

/*ES_t M_TIMER_enum_Timer0_GetCounts(){
//must see the counter incremented by ISR of overflow
}*/

ES_t M_TIMER_enum_Timer0_GetCounts(Timer0_cfg_type copy_cfg, u32* copy_counts){
	ES_t Local_enu_ErrorState= ES_NOK;
	switch (copy_cfg.WG_mode){
	case Normal:
		*copy_counts = TCNT0+(No_Of_overFlows*256);
		break;
	case CTC:
		*copy_counts = TCNT0+(No_Of_compareMatches*copy_cfg.OCR);
		break;
	default:
		Local_enu_ErrorState = ES_NOK;
		break;
	}

	return Local_enu_ErrorState;
}

ES_t M_TIMER_enum_Timer0_setDelayTimeMilliSec(Timer0_cfg_type copy_cfg,u32 millisec){
ES_t Local_enu_ErrorState= ES_NOK;
TIMER0_WG_mode_type mode=copy_cfg.WG_mode;

//calculate tick time
f32 Tick_time = (f32) copy_cfg.clk_source/CLK_FREQ;
//overall desired ticks
u32 Desired_ticks = millisec/(Tick_time*1000);
//approximate
 Local_no_of_overflows = Desired_ticks/256;
//number of counts before the first overflow
u32 No_of_remainingCounts;
//compare match(on CTC mode):
u32 OCR_value=255;

switch(mode){
	/*Normal mode*/
	case  Normal:
		//number of counts before the first overflow
		No_of_remainingCounts = Desired_ticks % 256;
		//if(number of remaining counts !=0
		if(No_of_remainingCounts){
			TCNT0 = (256-No_of_remainingCounts);
			Local_no_of_overflows++;
		}
		Local_enu_ErrorState=ES_OK;
		M_TIMER_enum_Timer0_start(copy_cfg);
		while(Local_no_of_overflows != No_Of_overFlows){}
		No_Of_overFlows=0;
		M_TIMER_enum_Timer0_stop();
	break;

	/*CTC mode*/
	case CTC:
		No_of_remainingCounts = Desired_ticks % OCR_value;
		//while OCR_value is not a factor of Desired_ticks
		while((Desired_ticks % OCR_value)){
			OCR_value--;
			local_no_of_compareMAtches = Desired_ticks / OCR_value;
			OCR0 = OCR_value;
			Timer0_cfg_type cfg_ctc= timer0_cfg1;
			cfg_ctc.OC_intterrupt_mode = OCI_Enabled;
			cfg_ctc.OCR=OCR_value;
		}
		Local_enu_ErrorState=ES_OK;
		M_TIMER_enum_Timer0_start(copy_cfg);
	break;

	default:
		Local_enu_ErrorState = ES_NOK;
	break;
	}
return Local_enu_ErrorState;
}

ES_t M_TIMER_enum_Timer0_EnableInt(){
	ES_t Local_enu_ErrorState = ES_OK;
	TIMSKR &= clr_OCIE;
	TIMSKR |= En_OCIE;
	return Local_enu_ErrorState;
}

ES_t M_TIMER_enum_Timer0_DisableInt(){
	ES_t Local_enu_ErrorState = ES_OK;
	TIMSKR &= clr_OCIE;
	TIMSKR &= ~(En_OCIE);
	return Local_enu_ErrorState;
}

ES_t M_TIMER_enum_Timer0_setCallBack(TIMER0_Int_type copy_Timer0_int_ID, void (*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter){
ES_t Local_enuErrorState = ES_NOK;
if (Copy_pfunAppFun != NULL){
	if(copy_Timer0_int_ID <=1){
	TIMER0_ApfunISRFun[copy_Timer0_int_ID  ] = Copy_pfunAppFun;
	TIMER0_ApvidISRParameter[ copy_Timer0_int_ID ] = Copy_pvidAppParameter;
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

ES_t M_TIMER_enum_Timer0_setFastPWM(Timer0_cfg_type copy_cfg,f32 copy_frequency ,f32 copy_duty){
	ES_t Local_enuErrorState= ES_OK;
	switch (copy_cfg.CO_mode){
	case 2:
		OCR0 = (((256*copy_duty)/100)-1);
		break;
	case 3:
		OCR0 = 255-((256*copy_duty)/100);
		break;
	default:
		Local_enuErrorState = ES_NOK;
		break;
	};
	TIMER0_clk_type desired_ps = CLK_FREQ/(256*copy_frequency);
	switch (desired_ps){
	case IO_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Clc_CS;
		break;
	case IO_8PS_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Clc_8PS_CS;
		break;
	case IO_64PS_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Clc_64PS_CS;
		break;
	case IO_256PS_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Clc_256PS_CS;
		break;
	case IO_1024_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Clc_1024PS_CS;
		break;
	case EXT_Falling_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Ext_Falling_CS;
		break;
	case EXT_Rising_clk:
		TCCR0 &= clr_CS;
		TCCR0 |= Ext_Rising_CS;
		break;
	default:
		Local_enuErrorState = ES_NOK;
		break;
	}

	return Local_enuErrorState;
}

ES_t M_TIMER_enum_Timer0_setphaseCorrectPWM(Timer0_cfg_type copy_cfg,f32 copy_frequency ,f32 copy_duty){
	ES_t Local_enuErrorState= ES_OK;
	switch (copy_cfg.CO_mode){
		case 2:
			OCR0 = ((255*copy_duty)/100);
			break;
		case 3:
			OCR0 = (255-((256*copy_duty)/100));
			break;
		default:
			Local_enuErrorState = ES_NOK;
			break;
		};
	TIMER0_clk_type desired_ps = CLK_FREQ/(510*copy_frequency);
	switch (desired_ps){
		case IO_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Clc_CS;
			break;
		case IO_8PS_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Clc_8PS_CS;
			break;
		case IO_64PS_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Clc_64PS_CS;
			break;
		case IO_256PS_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Clc_256PS_CS;
			break;
		case IO_1024_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Clc_1024PS_CS;
			break;
		case EXT_Falling_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Ext_Falling_CS;
			break;
		case EXT_Rising_clk:
			TCCR0 &= clr_CS;
			TCCR0 |= Ext_Rising_CS;
			break;
		default:
			Local_enuErrorState = ES_NOK;
			break;
		}

	return Local_enuErrorState;
}

ISR(TIMER0_OVF_vect)
{
	if (TIMER0_ApfunISRFun[OF_INT0] != NULL){
		if(No_Of_overFlows==Local_no_of_overflows){
		No_Of_overFlows=0;
		Local_no_of_overflows=0;
		TIMER0_ApfunISRFun [OF_INT0] (TIMER0_ApvidISRParameter[ OF_INT0 ]);
		M_TIMER_enum_Timer0_stop();
		}
		//TIMER0_ApfunISRFun [OF_INT0] (TIMER0_ApvidISRParameter[ OF_INT0 ]);
	}
	No_Of_overFlows++;
}


ISR(TIMER0_COMP_vect)
{

	if (TIMER0_ApfunISRFun[OC_INT0] != NULL){
		if(No_Of_compareMatches==local_no_of_compareMAtches){
		No_Of_compareMatches=0;
		local_no_of_compareMAtches=0;
			TIMER0_ApfunISRFun [OC_INT0] ( TIMER0_ApvidISRParameter[ OC_INT0 ] );
			M_TIMER_enum_Timer0_stop();
		}
	}
	No_Of_compareMatches++;
}
