#include "timer.h"
//time2定时器
//time3计数器
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
u16 display_step=0;
u16 IC2ReadValue=0;
u8 update=0;
void Timer_init(void)
{
     
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
    TIM_DeInit(TIM2);

	TIM_TimeBaseStructure.TIM_Period = 100; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =TIM2_ICPSC_DIV; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向下计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
    TIM_ARRPreloadConfig(TIM2, ENABLE); //允许ARR预装载缓冲器
     TIM2->CR1 |= TIM_CR1_OPM;
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, DISABLE);  //使能TIMx外设
/**********************************************************************************************************************/
	/* 允许TIM3的时钟 */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	 // GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
      
	  /* 将定时器3寄存器设为初始值 */
	   TIM_DeInit(TIM3);
		 
	   
		 
		  TIM_ICInitStructure.TIM_Channel	  = TIM_Channel_2;
		  TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
		  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
		  TIM_ICInitStructure.TIM_ICPrescaler = TIM3_ICPSC_DIV  ;
		  TIM_ICInitStructure.TIM_ICFilter	  = 0x3;
	  
		  TIM_ICInit(TIM3, &TIM_ICInitStructure);
		   /* Enable the TIM3 global Interrupt */
          NVIC_InitStructure.NVIC_IRQChannel                        = TIM3_IRQn;
          NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority      = 0;
          NVIC_InitStructure.NVIC_IRQChannelSubPriority             = 4;
          NVIC_InitStructure.NVIC_IRQChannelCmd                     = ENABLE;
          NVIC_Init(&NVIC_InitStructure);
		  /* TIM enable counter */
		  TIM_Cmd(TIM3, ENABLE);
	  
		  /* Enable the CC4 Interrupt Request */
		  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE); ///
	
}

void Timer_Update(u16 Update_counter       )
{

	
	TIM2->ARR=Update_counter;
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
	TIM_Cmd(TIM3, ENABLE);

}
u16 Is_Timer_Update(u16 update_data)
{
    static u16   IC2ReadValue1=0, IC2ReadValue2=0;
	  u16 circle_counter=0;
    
       
            /* Get the Input Capture value */
	if(update_data>6000)
	{    
		      IC2ReadValue2 = update_data;
           
           
            if(((IC2ReadValue2-IC2ReadValue1)>ERROR_TIME)||((IC2ReadValue1-IC2ReadValue2)>ERROR_TIME))
             {
							  TIM_Cmd(TIM2, DISABLE);  //使能TIMx外设  
							  TIM_Cmd(TIM3, DISABLE);
                 if (TIM3_ICPSC_DIV)
                     {
                     circle_counter=IC2ReadValue2/TIM3_ICPSC_DIV/360;
                     }
                     else
                     {
                         circle_counter=IC2ReadValue2/360;
                     }
                
            }
            else 
            {
                 circle_counter=0;                 
            }
            
            IC2ReadValue1=IC2ReadValue2;
					}
	else
	{
		  circle_counter=0; 
	}
        return circle_counter;


}


void TIM2_IRQHandler(void)   //TIM2中断,刻度计时器
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			
			display_step++; 
			 if(display_step>360)
		 {
			 display_step=0;
		 }	
      		 
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		 TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
		    //添加显示标志位
		}
}

void TIM3_IRQHandler(void)
{ 
	
    if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) 
    {
			update=1;
			TIM_Cmd(TIM3, DISABLE);
        /* Clear TIM2 Capture compare interrupt pending bit */
        
      IC2ReadValue= TIM_GetCapture2(TIM3);
				TIM3->CNT=0;
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
			TIM_Cmd(TIM3, ENABLE);
			
    }
}


