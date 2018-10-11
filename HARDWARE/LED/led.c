#include "stm32f10x.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//LED_Drive_V0.2开发板
//LED驱动代码	   
//修改日期:2018/7/31
//版本：V0.0.1
//版权所有，盗版必究。
//All rights reserved											  
////////////////////////////////////////////////////////////////////////////////// 	   
#if DIRVER_IC
uint8_t reg_val = 0;
uint8_t LEDOUT[4][4] ={0};
void LED_Init(void)
{
	u8 i;
	    LED_set_standby(FALSE);
	  IIC_Byte_Write(IIC_LED, LED0_ADDRESS,REG_ADDR_MODE1,0x00);
      IIC_Byte_Write(IIC_LED, LED0_ADDRESS,REG_ADDR_MODE2,0x04);
      IIC_Byte_Write(IIC_LED, LED1_ADDRESS,REG_ADDR_MODE1,0x00);
      IIC_Byte_Write(IIC_LED, LED1_ADDRESS,REG_ADDR_MODE2,0x04);
      IIC_Byte_Write(IIC_LED, LED2_ADDRESS,REG_ADDR_MODE1,0x00);
      IIC_Byte_Write(IIC_LED, LED2_ADDRESS,REG_ADDR_MODE2,0x04);
      IIC_Byte_Write(IIC_LED, LED3_ADDRESS,REG_ADDR_MODE1,0x00);
      IIC_Byte_Write(IIC_LED, LED3_ADDRESS,REG_ADDR_MODE2,0x04);
      delay_ms(5);  //delay until OSC is stable
      for(i=0;i<16;i++)
      {
            LED_set_duty_singlechannel(LED0_ADDRESS,i,2+i);
            LED_set_duty_singlechannel(LED1_ADDRESS,i,1+i);
            LED_set_duty_singlechannel(LED2_ADDRESS,i,1+i);
            LED_set_duty_singlechannel(LED3_ADDRESS,i,1+i);
	  
        }
   
    /* LED_pwm_on(LED0_ADDRESS,0,16);
	     LED_pwm_on(LED1_ADDRESS,0,16);
	     LED_pwm_on(LED2_ADDRESS,0,16);
	    LED_pwm_on(LED3_ADDRESS,0,16);*/
} 
void LED_set_standby(bool is_standby)
{
	if(is_standby == TRUE)
		{
		    LED_RESET =0;
			delay_us(1);   //tw
			 LED_RESET =1;
			delay_us(1);   //treset
		}
		else
		{
			LED_RESET =1;
			delay_ms(1);   //trec 0ns in theoretically
		}

}


void LED_set_channel(DeviceAddress_Typedef chip_addr,uint8_t channel,Tlc59116statemode_Typedef mode)
{   
    
    uint8_t reg_num = channel >> 2;
    uint8_t shift_num = channel % 4;
    u8 chip_num=0,channel_num=0;
    chip_num=(chip_addr&0x0f)/2;
    channel_num=channel/4;
	 LEDOUT[chip_num][channel_num]  = LEDOUT[chip_num][channel_num] & (~(0x03 << (2 * shift_num)));
     LEDOUT[chip_num][channel_num] = LEDOUT[chip_num][channel_num] | (mode << (2 * shift_num));     

    //uint8_t reg_val = 0;
	//IIC_Byte_Read(IIC_LED, chip_addr, &reg_val, REG_ADDR_LEDOUT0+reg_num);	
    //reg_val = reg_val & (~(0x03 << (2 * shift_num)));
    // reg_val = reg_val | (mode << (2 * shift_num)); 
	IIC_Byte_Write(IIC_LED, chip_addr, LEDOUT[chip_num][channel_num] ,REG_ADDR_LEDOUT0+reg_num);
	
}


u8 LED_set_duty_singlechannel(DeviceAddress_Typedef chip_addr,uint8_t channel,uint8_t duty)
{
	    uint8_t flag = 0;
		uint8_t offset;
	
		if(channel>15)
		{
			flag =	1;
		}
	
		else
		{
			offset = (REG_ADDR_PWM0+channel);
		    IIC_Byte_Write(IIC_LED, chip_addr,duty,offset);						
			LED_set_channel(chip_addr,channel,TLC_CH_PWM);
		}
	
		return flag;

}
u8 LED_set_duty_channels(DeviceAddress_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num,uint8_t *dutys)
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
            flag = LED_set_duty_singlechannel(chip_addr,start_channel+i,*(dutys+i));
            if(flag)
            {
                break;
            }
        }
    }

    return flag;


}

u8 LED_pwm_off(DeviceAddress_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num)
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
		   LED_set_channel(chip_addr,start_channel+i,TLC_CH_ON);
   }
   return flag;


}
u8 LED_pwm_on(DeviceAddress_Typedef chip_addr,uint8_t start_channel,uint8_t channel_num)
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
				LED_set_channel(chip_addr,start_channel+i,TLC_CH_OFF);
		}
		return flag;
}
#else
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟使能
	                                                //用于TIM3的CH2输出的PWM通过该LED显示
					
   //设置该引脚为复用输出功能,输出TIM4 CH3的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	 OEN =1;
	 LD =0;
   CLK =0;
   SDI=0; 
}
void LED_Output ( u8 output_flag,	u16 *p_data)
{
	u8 i;
	u16 outbuff;
	outbuff=*p_data;
	for(i=0;i<16;i++)
	  {
		  CLK =0;
			SDI=outbuff&0x0001;
		  outbuff=outbuff>>1;
		  CLK =1;	
	  }
		if(output_flag==ENABLE)
		{
	    LD =1;
	   OEN =0;	
		}
		 CLK =0;
}
/*void LED_Shutdown(void)
{
		u8 i;
	SDI=1;
	OEN=1;
	LD=1;
	for(i=0;i<4;i++)
	  {
		  CLK =0;
		  SDI=0;
		  CLK =1;	
	  }
	
}*/


#endif
