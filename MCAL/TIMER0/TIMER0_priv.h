/*
 * TIMER0_priv.h
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TIMER0_TIMER0_PRIV_H_
#define SRC_MCAL_TIMER0_TIMER0_PRIV_H_

#define	clr_WGM				0xB7	//clears the WGM bits
#define	Normal_WGM			0x00	//selects normal mode
#define PWM_PC_WGM			0x40	//selects PWM phase correct mode
#define CTC_WGM				0x08	//selects CTC mode
#define PWM_FAST_WGM		0x48	//selects fast PWM mode

#define clr_COM				0xCF	//clears the COM bits
#define Dis_Dis_COM			0x00	//selects disconnected CO
#define Tog_Res_COM			0x10	//selects toggle CO for non_PWM and nothing for PWM
#define Clr_Clr_COM			0x20	//selects clear CO for all modes
#define	Set_Set_COM			0x30	//selects set CO for all modes

#define clr_CS				0xF8	//clears the CS bits
#define NO_clc_CS			0x00	//selects no clock source
#define Clc_CS				0x01	//selects full clock freq
#define Clc_8PS_CS			0x02	//selects IO clock/8 freq
#define Clc_64PS_CS			0x03	//selects IO clock/64 freq
#define Clc_256PS_CS		0x04	//selects IO clock/256 freq
#define Clc_1024PS_CS		0x05	//selects IO clock/1024 freq
#define Ext_Falling_CS		0x06	//selects external clock on falling edge
#define Ext_Rising_CS		0x07	//selects external clock on rising edge

#define clr_TOIE			0xFE	//clears the overflow interrupt bit
#define En_TOIE				0x01	//enables the overflow interrupt
#define clr_OCIE			0xFD	//clears the OC interrupt bit
#define En_OCIE				0x02	//enables the OC interrupt



#endif /* SRC_MCAL_TIMER0_TIMER0_PRIV_H_ */
