#ifndef __I2C_H
#define __I2C_H	 
#include "stm32f10x.h"
//I2C驱动代码			 
//2018/7/31
#define EEPROM_IIC         0X00  // 地址	
#define LED_IIC            0X01  // 地址	
typedef enum { false=0, true=!false } bool ;
void IIC_Configuration(void);
void IIC_Byte_Write( bool iic_x, u8 Device_Address, u8 pBuffer, u8 Word_Address);
void IIC_Wait_EEprom( bool iic_x, u8 Device_Address);
void IIC_Byte_Read(  bool iic_x, u8 Device_Address, u8* pRead, u8 Word_Address);

#endif