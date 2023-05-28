/*
 * TIMER1_Priv.h
 *
 *  Created on: Feb 26, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TIMER1_TIMER1_PRIV_H_
#define SRC_MCAL_TIMER1_TIMER1_PRIV_H_

#define T1_clr_COMA					0x3F	//clears the COM bits
#define T1_Dis_Dis_Dis_COMA			0x00	//selects disconnected CO
#define T1_Tog_Tog_Tog_COMA			0x40	//selects toggle CO for non_PWM and nothing for PWM
#define T1_Clr_Clr_Clr_COMA			0x80	//selects clear CO for modes modes
#define	T1_Set_Set_Set_COMA			0xC0	//selects set CO for all modes

#define T1_clr_COMB					0xCF	//clears the COM bits
#define T1_Dis_Dis_Dis_COMB			0x00	//selects disconnected CO
#define T1_Tog_Tog_Tog_COMB			0x10	//selects toggle CO for non_PWM and nothing for PWM
#define T1_Clr_Clr_Clr_COMB			0x20	//selects clear CO for modes modes
#define	T1_Set_Set_Set_COMB			0x30	//selects set CO for all modes

#define	T1_clr_WGM10				0xFC	//clears the WGM bits
#define	T1_Normal_WGM10				0x00	//selects normal mode
#define T1_CTC_OCRA_WGM10			0x00	//selects CTC mode
#define T1_CTC_ICR_WGM10			0x00	//selects CTC mode
#define T1_PWM_FAST_8_WGM10			0x01	//selects fast PWM mode
#define T1_PWM_FAST_9_WGM10			0x02	//selects fast PWM mode
#define T1_PWM_FAST_10_WGM10		0x03	//selects fast PWM mode
#define T1_PWM_FAST_ICR_WGM10		0x02	//selects fast PWM mode
#define T1_PWM_FAST_OCRA_WGM10		0x03	//selects fast PWM mode
#define T1_PWM_PC_8_WGM10			0x01	//selects PWM phase correct mode
#define T1_PWM_PC_9_WGM10			0x02	//selects PWM phase correct mode
#define T1_PWM_PC_10_WGM10			0x03	//selects PWM phase correct mode
#define T1_PWM_PC_ICR_WGM10			0x02	//selects PWM phase and frequency correct mode
#define T1_PWM_PC_OCRA_WGM10		0x03	//selects PWM phase and frequency correct mode
#define T1_PWM_PfC_ICR_WGM10		0x00	//selects PWM phase and frequency correct mode
#define T1_PWM_PfC_OCRA_WGM10		0x01	//selects PWM phase and frequency correct mode

#define	T1_clr_WGM32				0xC7	//clears the WGM bits
#define	T1_Normal_WGM32				0x00	//selects normal mode
#define T1_CTC_OCRA_WGM32			0x08	//selects CTC mode
#define T1_CTC_ICR_WGM32			0x18	//selects CTC mode
#define T1_PWM_FAST_8_WGM32			0x08	//selects fast PWM mode
#define T1_PWM_FAST_9_WGM32			0x08	//selects fast PWM mode
#define T1_PWM_FAST_10_WGM32		0x08	//selects fast PWM mode
#define T1_PWM_FAST_ICR_WGM32		0x18	//selects fast PWM mode
#define T1_PWM_FAST_OCRA_WGM32		0x18	//selects fast PWM mode
#define T1_PWM_PC_8_WGM32			0x00	//selects PWM phase correct mode
#define T1_PWM_PC_9_WGM32			0x00	//selects PWM phase correct mode
#define T1_PWM_PC_10_WGM32			0x00	//selects PWM phase correct mode
#define T1_PWM_PC_ICR_WGM32			0x10	//selects PWM phase and frequency correct mode
#define T1_PWM_PC_OCRA_WGM32		0x10	//selects PWM phase and frequency correct mode
#define T1_PWM_PfC_ICR_WGM32		0x10	//selects PWM phase and frequency correct mode
#define T1_PWM_PfC_OCRA_WGM32		0x10	//selects PWM phase and frequency correct mode

#define T1_clr_Nc					0x3F	//clear noise canceler bit
#define T1_En_NC					0x80	//enables noise canceler

#define T1_clr_ICES					0xBF	//clear input capture edge selection bit
#define	T1_RE_ICES					0x40	//trigger with rising edge

#define T1_clr_CS					0xF8	//clears the CS bits
#define T1_NO_clc_CS				0x00	//selects no clock source
#define T1_Clc_CS					0x01	//selects full clock freq
#define T1_Clc_8PS_CS				0x02	//selects IO clock/8 freq
#define T1_Clc_64PS_CS				0x03	//selects IO clock/64 freq
#define T1_Clc_256PS_CS				0x04	//selects IO clock/256 freq
#define T1_Clc_1024PS_CS			0x05	//selects IO clock/1024 freq
#define T1_Ext_Falling_CS			0x06	//selects external clock on falling edge
#define T1_Ext_Rising_CS			0x07	//selects external clock on rising edge

#define T1_clr_TOIE					0xFB	//clears the overflow interrupt bit
#define T1_En_TOIE					0x04	//enables the overflow interrupt
#define T1_clr_OCIEB				0xF7	//clears the OCB interrupt bit
#define T1_En_OCIEB					0x08	//enables the OCB interrupt
#define T1_clr_OCIEA				0xEF	//clears the OCA interrupt bit
#define T1_En_OCIEA					0x10	//enables the OCA interrupt
#define T1_clr_TICE					0xDF	//clears the input capture interrupt bit
#define T1_En_TICE					0x20	//enables the input capture interrupt

#define T1_set_ICF					0x20	//set the input capture flag

#endif /* SRC_MCAL_TIMER1_TIMER1_PRIV_H_ */
