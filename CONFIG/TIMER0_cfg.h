/*
 * TIMER0_cfg.h
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmed
 */

#ifndef SRC_CONFIG_TIMER0_CFG_H_
#define SRC_CONFIG_TIMER0_CFG_H_
#include "STD_TYPES.h"
#include "TIMER_types.h"

typedef struct{
	TIMER0_WG_mode_type WG_mode;
	TIMER0_CO_mode_type CO_mode;
	TIMER0_clk_type clk_source;
	TIMER0_OF_Interrupt_mode_type OF_intterrupt_mode;
	TIMER0_OC_Interrupt_mode_type OC_intterrupt_mode;
	u8 OCR;
}Timer0_cfg_type;

#define CLK_FREQ 16000000

#endif /* SRC_CONFIG_TIMER0_CFG_H_ */
