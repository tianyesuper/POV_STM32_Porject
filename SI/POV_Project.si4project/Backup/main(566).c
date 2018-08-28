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
	   NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	   GPIO_Configuration();
 //	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	 delay_init(72);	    	 //��ʱ������ʼ��	  
	 uart_init(115200);
	 IIC_Configuration();
     LED_Init();			     //LED�˿ڳ�ʼ��
      DS1302_SetupTime(&Time_Structure);
      EXTIX_Init();
      __enable_irq();
     
// TIME_Init();
		while(1)
	    {
 	       DS1302_ReadTime(&Time_Structure);
 	       ifp= Remote_Process();   //������յ����ݴ���
				
	     	}
 }

