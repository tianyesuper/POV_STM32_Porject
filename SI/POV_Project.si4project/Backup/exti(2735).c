void EXTIX_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;


  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//???jtag

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);


  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
 // ??'?? WK_UP-->GPIOA.0	  ????????
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  //GPIOA.13 ????????????'??????
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 


  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  

	


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
  
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;		
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure);  	 
}

 
void EXTI1_IRQHandler(void)
{
    delay_ms(10);   
  	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	 
	{	  
		LED0=!LED0;
		LED1=!LED1;	
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  
}
 
void EXTI9_5_IRQHandler(void)
{
  	delay_ms(10);  
 
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
	 	LED0=!LED0;
	}
 
     else if (EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
		LED1=!LED1;
	}
	 EXTI_ClearITPendingBit(EXTI_Line13);  
	 EXTI_ClearITPendingBit(EXTI_Line15);  
}
