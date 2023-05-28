/*
 * TWI_types.h
 *
 *  Created on: Mar 9, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_TWI_TWI_TYPES_H_
#define SRC_MCAL_TWI_TWI_TYPES_H_

typedef enum{
	TWI_CLK1,
	TWI_CLK4,
	TWI_CLK16,
	TWI_CLK64
}TWI_PRESCALLER_t;

typedef enum{
	BR_0,
	BR_100KHZ 	=72,
	BR_400KHZ	=12
}TWI_BITRATE_t;
#endif /* SRC_MCAL_TWI_TWI_TYPES_H_ */
