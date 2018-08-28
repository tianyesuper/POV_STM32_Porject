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
    u8 ifp=0;
    TIME_TypeDef Time_Structure;
    Time_Structure.sec=0;
    Time_Structure.min=0;
    Time_Structure.hour=21;
    Time_Structure.week=2;
    Time_Structure.date=14;
    Time_Structure.month=8;
    Time_Structure.year=18;
    // unsigned char time[20]="\0";
	   NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	   GPIO_Configuration();
 //	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	 delay_init(72);	    	 //延时函数初始化	  
	 uart_init(115200);
	 IIC_Configuration();
     LED_Init();			     //LED端口初始化
      DS1302_SetupTime(&Time_Structure);
      EXTIX_Init();
      __enable_irq();
     
// TIME_Init();
		while(1)
	    {
 	       DS1302_ReadTime(&Time_Structure);
 	       ifp= Remote_Process();   //红外接收到数据处理
				
	     	}
 }

