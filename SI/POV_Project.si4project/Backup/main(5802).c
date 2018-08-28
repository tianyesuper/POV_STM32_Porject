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
    TIME_TypeDef Time_InitStructure;
    Time_InitStructure.sec=0;
    Time_InitStructure.min=0;
    Time_InitStructure.hour=21;
    Time_InitStructure.week=2;
    Time_InitStructure.date=14;
    Time_InitStructure.month=8;
    Time_InitStructure.year=18;
    
    
    
    // unsigned char time[20]="\0";
	   NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	   GPIO_Configuration();
 //	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	 delay_init(72);	    	 //��ʱ������ʼ��	  
	 uart_init(115200);
	 IIC_Configuration();
     LED_Init();			     //LED�˿ڳ�ʼ��
      DS1302_SetupTime(&Time_InitStructure);
      
       
// TIME_Init();
		while(1)
	    {
 	       DS1302_ReadTime(&Time_InitStructure);
	     	}
 }

