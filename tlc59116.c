/**
  ************************************************************************
* @file: tlc59116.c
* @author: chenheng
* @date:  11-29-2016
* @brief:
* @attention:
  ************************************************************************
  */

#include "tlc59116.h"
#include "global.h"

/**
  *@ brief:  enable the clock resources of LEDS
  *@ param: none
  *@ retval:none
  */
static void tlc59116_rcc_init(void)
{
    RCC_APB2PeriphClockCmd(TLC59116_RCC, ENABLE);
}

/**
  * @brief  set the pin mode of the LEDs
  * @param  none
  * @retval none
  */
static void tlc59116_pin_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = TLC59116_GPIO_MODE;
    GPIO_InitStructure.GPIO_Speed = TLC59116_GPIO_SPEED;

    GPIO_InitStructure.GPIO_Pin = TLC59116_RESET_IC_PIN;
    GPIO_Init(TLC59116_RESET_IC_PORT, &GPIO_InitStructure);
}

/**
  *@ brief: whether set stand by mode
  *@ param: is_standby: TRUE : set standby mode FALSE:awake from standby mode
  *@ retval: none
  */
void tlc59116_set_standby(bool_t is_standby)
{
    if(is_standby == TRUE)
    {
        GPIO_ResetBits(TLC59116_RESET_IC_PORT,TLC59116_RESET_IC_PIN);
        delay_us(1);   //tw
        GPIO_SetBits(TLC59116_RESET_IC_PORT,TLC59116_RESET_IC_PIN);
        delay_us(1);   //treset
    }
    else
    {
        GPIO_SetBits(TLC59116_RESET_IC_PORT,TLC59116_RESET_IC_PIN);
        delay_ms(1);   //trec 0ns in theoretically
    }

}

static void tlc59116_write_reg(Tlc59116chipaddr_Typedef chip_addr,uint8_t reg, uint8_t value)
{
    uint8_t flag = 0;
		
		uint8_t wr_dat = value;
	
    flag = iic_write_datas(I2C1,chip_addr,(uint8_t)reg,&wr_dat,1);
    if (flag)
    {
        while(1);
    }
}
static uint8_t tlc59116_red_reg(Tlc59116chipaddr_Typedef chip_addr,uint8_t reg)
{
    uint8_t flag = 0;
	uint8_t reg_val = 0;

    flag = iic_read_datas(I2C1,chip_addr,(uint8_t)reg,&reg_val,1);
    if (flag)
    {
        while(1);
    }
	return reg_val;
}


static void tlc59116_init_controller(void)
{
    tlc59116_write_reg(CHIP_ADDR_1,REG_ADDR_MODE1,0x00);
    tlc59116_write_reg(CHIP_ADDR_1,REG_ADDR_MODE2,0x00);
    tlc59116_write_reg(CHIP_ADDR_2,REG_ADDR_MODE1,0x00);
    tlc59116_write_reg(CHIP_ADDR_2,REG_ADDR_MODE2,0x00);
    tlc59116_write_reg(CHIP_ADDR_3,REG_ADDR_MODE1,0x00);
    tlc59116_write_reg(CHIP_ADDR_3,REG_ADDR_MODE2,0x00);
    tlc59116_write_reg(CHIP_ADDR_4,REG_ADDR_MODE1,0x00);
    tlc59116_write_reg(CHIP_ADDR_4,REG_ADDR_MODE2,0x00);
    tlc59116_write_reg(CHIP_ADDR_5,REG_ADDR_MODE1,0x00);
    tlc59116_write_reg(CHIP_ADDR_5,REG_ADDR_MODE2,0x00);
}


/**
  * @brief  initialise the module of leds of the board
  * @param  None
  * @retval None
  */
void tlc59116_init(void)
{
    tlc59116_rcc_init();
    tlc59116_pin_init();
    tlc59116_set_standby(FALSE);

	iic_init();
    tlc59116_init_controller();
    delay_ms(5);  //delay until OSC is stable
    
	tlc59116_pwm_off(CHIP_ADDR_1,0,16);
	tlc59116_pwm_off(CHIP_ADDR_2,0,16);
	tlc59116_pwm_off(CHIP_ADDR_3,0,16);
	tlc59116_pwm_off(CHIP_ADDR_4,0,16);
	tlc59116_pwm_off(CHIP_ADDR_5,0,16);

}


/**
 *  @brief      tlc59116 open channel.
 *  @param[out] NULL.
 *  @return     NULL.
 */
void tlc59116_set_channel(Tlc59116chipaddr_Typedef chip_addr,uint8_t channel,Tlc59116statemode_Typedef mode)
{
    uint8_t reg_num = channel >> 2;
    uint8_t shift_num = channel % 4;
    uint8_t reg_val = 0;

	reg_val = tlc59116_red_reg(chip_addr,REG_ADDR_LEDOUT0+reg_num);
    reg_val = reg_val & (~(0x03 << (2 * shift_num)));
    // set
    reg_val = reg_val | (mode << (2 * shift_num));
    // sensor_info("TLC59116 writeregister:%d ,reg_val:%d\r\n", reg_num, reg_val);
	tlc59116_write_reg(chip_addr,REG_ADDR_LEDOUT0+reg_num,reg_val);
}


/**
  * @brief  set the duty of single output channel
  * @param  chip_addr:the address of chip
            channel:indicate which output channel will be set (0~15)
            duty:the param arrange is 0~255 (val = duty/256)
  * @retval 0:success 1:fail
  */
uint8_t tlc59116_set_duty_singlechannel(Tlc59116chipaddr_Typedef chip_addr,uint8_t channel,uint8_t duty)
{
    uint8_t flag = 0;
    uint8_t offset;

    if(channel>15)
    {
        flag =  1;
    }

    else
    {
        offset = (REG_ADDR_PWM0+channel);
		tlc59116_write_reg(chip_addr,offset,255-duty);
		
        tlc59116_set_channel(chip_addr,channel,TLC_CH_PWM);
    }

    return flag;
}



/**
  * @brief  set the duty of some continual output channels
  * @param  chip_addr:the address of chip
            start_channel:indicate which output channel will be set (0~15)
            channel_num:indicate how many registers will be set (0~15)
            duty:the param arrange is 0~255 (val = duty/256)
  * @retval None
  */
uint8_t tlc59116_set_duty_channels(Tlc59116chipaddr_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num,uint8_t *dutys)
{
    uint8_t flag = 0;
    uint8_t i;

    if(channel_num == 0)
    {
        flag = 1;
    }
    else if(channel_num > 16)
    {
        flag = 1;
    }
    else if((channel_num +start_channel) > 16)
    {
        flag = 1;
    }

    else
    {
        for(i=0; i<channel_num; i++)
        {
            flag = tlc59116_set_duty_singlechannel(chip_addr,start_channel+i,*(dutys+i));
            if(flag)
            {
                break;
            }
        }
    }

    return flag;
}


uint8_t tlc59116_pwm_off(Tlc59116chipaddr_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num)
{
    uint8_t flag = 0;
    uint8_t i;

    if(channel_num == 0)
    {
        flag = 1;
    }
    else if(channel_num > 16)
    {
        flag = 1;
    }
    else if((channel_num +start_channel) > 16)
    {
        flag = 1;
    }
	else
	{
		for(i=0; i<channel_num; i++)
			tlc59116_set_channel(chip_addr,start_channel+i,TLC_CH_ON);
	}
	return flag;
}


uint8_t tlc59116_pwm_on(Tlc59116chipaddr_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num)
{
    uint8_t flag = 0;
    uint8_t i;

    if(channel_num == 0)
    {
        flag = 1;
    }
    else if(channel_num > 16)
    {
        flag = 1;
    }
    else if((channel_num +start_channel) > 16)
    {
        flag = 1;
    }
	else
	{
		for(i=0; i<channel_num; i++)
			tlc59116_set_channel(chip_addr,start_channel+i,TLC_CH_OFF);
	}
	return flag;
}



