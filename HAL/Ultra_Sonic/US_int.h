/*
 * US_int.h
 *
 *  Created on: Mar 2, 2023
 *      Author: ahmed
 */

#ifndef SRC_HAL_ULTRA_SONIC_US_INT_H_
#define SRC_HAL_ULTRA_SONIC_US_INT_H_
ES_t H_US_enu_init();
ES_t H_US_enu_calculate_distance(f32 * copy_distance_ptr);
ES_t H_US_enu__edgeProcessing(void);
 void H_US_enu_send_trig();

#endif /* SRC_HAL_ULTRA_SONIC_US_INT_H_ */
