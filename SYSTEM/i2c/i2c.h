#ifndef __I2C_H
#define __I2C_H	 
#include "stm32f10x.h"
#include "led.h"
//I2C��������			 
//2018/7/31 

typedef enum
{
   IIC_EEPROM=0, IIC_LED=1,
   } 
IIC_Typedef ;

typedef enum
{
  EEPROM_ADDRESS= 0XC0,  // ��ַ	
  LED0_ADDRESS=  0XC0,   // ��ַ	
  LED1_ADDRESS=  0XC2,   // ��ַ	
  LED2_ADDRESS=  0XC4,   // ��ַ	
  LED3_ADDRESS=  0XC6, 
   } 
DeviceAddress_Typedef ;

void IIC_Configuration(void);
void IIC_Byte_Write( IIC_Typedef iic_x, DeviceAddress_Typedef Device_Address, u8 pBuffer, u8 Word_Address);
void IIC_Wait_Nobusy( IIC_Typedef iic_x, DeviceAddress_Typedef Device_Address);
void IIC_Byte_Read(  IIC_Typedef iic_x, DeviceAddress_Typedef Device_Address, u8 * pRead, u8 Word_Address);

#endif
