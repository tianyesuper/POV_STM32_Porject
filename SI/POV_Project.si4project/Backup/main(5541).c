#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"
#include "usart.h"
#include "i2c.h"
#include "beep.h"
#include "exti.h"
#include "DS1302.h"
#include "eeprom.h"
#include "infrared.h"

	
 int main(void)
 {
     unsigned char time[20]="\0";
	   NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	   GPIO_Configuration();
 //	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	 delay_init(72);	    	 //延时函数初始化	  
	 uart_init(115200);
	 IIC_Configuration();
     LED_Init();			     //LED端口初始化
// TIME_Init();
		while(1)
	{
 	
		}
 }

