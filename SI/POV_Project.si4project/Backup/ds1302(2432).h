#ifndef __DS1302_H
#define __DS1302_H	 
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"


//DS1302驱动代码			 
//2012/2/27
//#define LED_RESET      PBout(2)// PA8
typedef struct
{
	unsigned char  sec;
	unsigned char  min;
	unsigned char  hour;
	unsigned char  week;
	unsigned char  date;
	unsigned char  month;
	unsigned char  year;
}TIME_TypeDef;
	

//*****************DS1302控制命令*******************
#define   RdSec  						0x81
#define   RdMin  						0x83
#define   RdHour  						0x85
#define   RdDate  						0x87
#define   RdMonth  						0x89
#define   RdWeek  						0x8b
#define   RdYear  						0x8d
#define   RdControl          			0x8f
#define   RdTrickleCharge 				0x91
#define   RdClockBurst  				0xbf
#define   WrSec  						0x80
#define   WrMin  						0x82
#define   WrHour  						0x84
#define   WrDate  						0x86
#define   WrMonth  						0x88
#define   WrWeek  						0x8a
#define   WrYear  						0x8c
#define   WrControl         			0x8e
#define   WrTrickleCharge 				0x90
#define   WrClockBurst  				0xbe
#define   RdRamBurst 					0xbf
#define   DS1302_READ_SDA()    (GPIO_ReadInputDataBit(DS1302_PORT, DS1302_IO_PIN))

#define   IO_OUT           PBout(13)// PB13
#define   IO_IN            PBin(13)// PB13

extern void DS1302_Init(void);//初始化


//内部函数
static void DS1302_IO_OUT(void);
static void DS1302_IO_IN(void);
static void DS1302_Write8bit(u8 code);
static u8   DS1302_Read8bit(void);
static void DS1302_ReadBurst(unsigned char *rstr);

//外部函数

extern u8   DS1302_ReadByte(u8 con);
extern void DS1302_WriteByte(u8 con,u8 code);
extern void DS1302_WriteTime(TIME_TypeDef* time);
extern void DS1302_ReadTime(TIME_TypeDef* time);

void time_convert(TIME_TypeDef *time_get);


		 				    
#endif
