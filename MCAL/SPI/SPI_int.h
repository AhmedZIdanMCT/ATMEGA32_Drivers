/*
 * SPI_int.h
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */

#ifndef SRC_MCAL_SPI_SPI_INT_H_
#define SRC_MCAL_SPI_SPI_INT_H_

ES_t M_SPI_enu_init(SPI_CFG_TYPE copy_SPI_cfg);
ES_t M_SPI_enu_transferByteSynch(u8* copy_transmit_data,u8* copy_receive_data);
ES_t M_SPI_enu_transferString(u8* copy_transmit_data);
ES_t M_SPI_enu_receiveByteSynch(u8* copy_receive_data);
ES_t M_SPI_enu_receiveByteAsynchCallBack(u8* copy_receive_data);
ES_t M_SPI_enum_setCallBack(void(*Copy_pfunAppFun)(void*), void * Copy_pvidAppParameter);




#endif /* SRC_MCAL_SPI_SPI_INT_H_ */
