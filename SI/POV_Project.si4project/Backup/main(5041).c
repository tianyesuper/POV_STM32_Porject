#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"
#include "usart.h"
#include "i2c.h"








	
 int main(void)
 {
	 NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 //	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	 delay_init(72);	    	 //延时函数初始化	  
	 uart_init(115200);
   LED_Init();			     //LED端口初始化
// TIME_Init();
	/*	while(1)
	{
 		LED0=0;				 //  这里使用了位带操作，也可以使用 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
 		LED1=1;	 			 //	 也可以使用   GPIO_SetBits(GPIOD,GPIO_Pin_2);
		delay_ms(300);		 
 	 	LED0=1;	             //	 也可以使用	  GPIO_SetBits(GPIOA,GPIO_Pin_8);	    
  		LED1=0; 			 // 也可以使用	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;
		delay_ms(300);	
		}*/
 }

