#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"
#include "usart.h"
#include "i2c.h"








	
 int main(void)
 {
	 NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 //	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	 delay_init(72);	    	 //��ʱ������ʼ��	  
	 uart_init(115200);
   LED_Init();			     //LED�˿ڳ�ʼ��
// TIME_Init();
	/*	while(1)
	{
 		LED0=0;				 //  ����ʹ����λ��������Ҳ����ʹ�� GPIO_ResetBits(GPIOA,GPIO_Pin_8);
 		LED1=1;	 			 //	 Ҳ����ʹ��   GPIO_SetBits(GPIOD,GPIO_Pin_2);
		delay_ms(300);		 
 	 	LED0=1;	             //	 Ҳ����ʹ��	  GPIO_SetBits(GPIOA,GPIO_Pin_8);	    
  		LED1=0; 			 // Ҳ����ʹ��	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;
		delay_ms(300);	
		}*/
 }

