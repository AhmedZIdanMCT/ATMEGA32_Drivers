/*
 * ADC_Lcfg.c
 *
 *  Created on: Mar 3, 2023
 *      Author: ahmed
 */

#include "ADC_Types.h"
#include "ADC_cfg.h"
const ADC_cfg_type ADC1_config[1] = {
				{PRES_128,
				CHNL_1,
				SINGLE_CONV,
				POLLING,
				FREE_RUNINNG,
				AVCC_REF,
				RIGHT_ADJ}
};
