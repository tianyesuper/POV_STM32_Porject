#ifndef __TLC59116_H__
#define __TLC59116_H__

#include "stm32f10x.h"
#include "global.h"
#include "i2c.h"

typedef enum{
  TLC_CH_OFF = 0,
  TLC_CH_ON = 1,
  TLC_CH_PWM = 2,
  TLC_CH_G_PWM = 3
}Tlc59116statemode_Typedef;



typedef enum
{
    /*Register address, followed by reset the default values */
    CHIP_ADDR_1 = 0xc0,
    CHIP_ADDR_2  = 0xc2, 
    CHIP_ADDR_3  = 0xc4, 
    CHIP_ADDR_4  = 0xc6,
    CHIP_ADDR_5   = 0xc8,
}Tlc59116chipaddr_Typedef;


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
#define REG_ADDR_PWM9   (0x0b)
#define REG_ADDR_PWM10   (0x0c)
#define REG_ADDR_PWM11 (0x0d)
#define REG_ADDR_PWM12   (0x0e)
#define REG_ADDR_PWM13   (0x0f)
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
    


#define TLC59116_RCC (RCC_APB2Periph_GPIOA) 


#define TLC59116_GPIO_MODE   (GPIO_Mode_Out_PP)
#define TLC59116_GPIO_SPEED  (GPIO_Speed_50MHz)

#define TLC59116_RESET_IC_PORT (GPIOA)
#define TLC59116_RESET_IC_PIN    (GPIO_Pin_8)

void tlc59116_set_standby(bool_t is_standby);
void tlc59116_init(void);

uint8_t tlc59116_set_duty_singlechannel(Tlc59116chipaddr_Typedef chip_addr,uint8_t channel,uint8_t duty);
uint8_t tlc59116_set_duty_channels(Tlc59116chipaddr_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num,uint8_t *dutys);
uint8_t tlc59116_pwm_off(Tlc59116chipaddr_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num);
uint8_t tlc59116_pwm_on(Tlc59116chipaddr_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num);

#endif
