/*
 * TIMER_types.h
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TIMER0_TIMER_TYPES_H_
#define SRC_MCAL_TIMER0_TIMER_TYPES_H_

typedef enum{
	Normal,
	PhaseCorrect_PWM,
	CTC,
	Fast_PWM
}TIMER0_WG_mode_type;

typedef enum{
	Disconnected,
	Toogle,
	Clear,
	Set
}TIMER0_CO_mode_type;

typedef enum{
	OFI_Disabled,
	OFI_Enabled
}TIMER0_OF_Interrupt_mode_type;

typedef enum{
	OCI_Disabled,
	OCI_Enabled
}TIMER0_OC_Interrupt_mode_type;

typedef enum{
	No_clk,
	IO_clk=1,
	IO_8PS_clk = 8,
	IO_64PS_clk =64,
	IO_256PS_clk =256,
	IO_1024_clk =1024,
	EXT_Falling_clk,
	EXT_Rising_clk
}TIMER0_clk_type;

typedef enum{
	OF_INT0,
	OC_INT0
}TIMER0_Int_type;


#endif /* SRC_MCAL_TIMER0_TIMER_TYPES_H_ */
