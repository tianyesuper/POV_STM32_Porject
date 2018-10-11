#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "sys.h"
#include "i2c.h"
#include "delay.h"
//DIRVER_IC  1,支持TLC59116,0支持AS1110.
#define  DIRVER_IC  0
#if DIRVER_IC
//LED驱动代码			 
//2012/2/27

//LED端口定义

typedef enum
{
  TLC_CH_OFF = 0,
  TLC_CH_ON = 1,
  TLC_CH_PWM = 2,
  TLC_CH_G_PWM = 3
}Tlc59116statemode_Typedef;

typedef struct
{
	u8  LEDOUT0;
	u8  LEDOUT1;
	u8  LEDOUT2;
	u8  LEDOUT3;
	
}TLC_CH_TypeDef;


/*Register address, followed by reset the default values */
#define REG_ADDR_MODE1 (0x00)
#define REG_ADDR_MODE2  (0x01)
#define REG_ADDR_PWM0   (0x02)
#define REG_ADDR_PWM1 (0x03)
#define REG_ADDR_PWM2 (0x04)
#define REG_ADDR_PWM3 (0x05)
#define REG_ADDR_PWM4 (0x06)
#define REG_ADDR_PWM5 (0x07)
#define REG_ADDR_PWM6 (0x08)
#define REG_ADDR_PWM7   (0x09)
#define REG_ADDR_PWM8   (0x0A)
#define REG_ADDR_PWM9   (0x0B)
#define REG_ADDR_PWM10   (0x0C)
#define REG_ADDR_PWM11 (0x0D)
#define REG_ADDR_PWM12   (0x0E)
#define REG_ADDR_PWM13   (0x0F)
#define REG_ADDR_PWM14 (0x10)
#define REG_ADDR_PWM15 (0x11)
#define REG_ADDR_GRPPWM (0x12)
#define REG_ADDR_GRPFREQ   (0x13)
#define REG_ADDR_LEDOUT0   (0x14)
#define REG_ADDR_LEDOUT1     (0x15)
#define REG_ADDR_LEDOUT2     (0x16)
#define REG_ADDR_LEDOUT3     (0x17)
#define REG_ADDR_SUBADR1   (0x18)
#define REG_ADDR_SUBADR2     (0x19)
#define REG_ADDR_SUBADR3     (0x1A)
#define REG_ADDR_ALLCALLADR   (0x1B)
#define REG_ADDR_IREF     (0x1C)
#define REG_ADDR_EFLAG1   (0x1D)
#define REG_ADDR_EFLAG2   (0x1E)

void LED_Init(void);//初始化
void LED_set_standby(bool is_standby);

u8 LED_set_duty_singlechannel(DeviceAddress_Typedef chip_addr,uint8_t channel,uint8_t duty);
u8 LED_set_duty_channels(DeviceAddress_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num,uint8_t *dutys);
u8 LED_pwm_off(DeviceAddress_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num);
u8 LED_pwm_on(DeviceAddress_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num);
#else

#define CLK PBin(2)	 //时钟输出脚
#define SDI PBin(10)	 //数据输出脚
#define LD  PBin(1)	 //串行数据导入脚
#define OEN PBin(0)	 //输出使能脚


void LED_Init(void);//初始化
void LED_Output( u8 output_flag,	u16 *p_data);
//void LED_Shutdown(void);



#endif

		 				    
#endif
