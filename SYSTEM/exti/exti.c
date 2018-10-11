#include "exti.h"


void EXTIX_Init(void)
{
  	  GPIO_InitTypeDef GPIO_InitStructure; 
 	    EXTI_InitTypeDef EXTI_InitStructure;
 	    NVIC_InitTypeDef NVIC_InitStructure;


  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);


  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);  	//选择PA1所在的GPIO管脚用作外部中断线路EXIT1		
 
	  EXTI_InitStructure.EXTI_Line = EXTI_Line1;	//外部线路EXIT1
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//设外外部中断模式:EXTI线路为中断请求  EXTI_Mode_Event ;//设置 EXTI线路为事件请求 
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //外部中断触发沿选择:设置输入线路下降沿为中断请求
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;		//使能外部中断新状态
	  EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器	

  
      NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //使能按键所在的外部中断通道
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2; //从优先级1级
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	  NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	 
}

 


