#include "timer.h"
//time2��ʱ��
//time3������
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
u16 display_step=0;
u16 IC2ReadValue=0;
u8 update=0;
void Timer_init(void)
{
     
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
    TIM_DeInit(TIM2);

	TIM_TimeBaseStructure.TIM_Period = 100; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =TIM2_ICPSC_DIV; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���¼���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ARRPreloadConfig(TIM2, ENABLE); //����ARRԤװ�ػ�����
     TIM2->CR1 |= TIM_CR1_OPM;
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx����
/**********************************************************************************************************************/
	/* ����TIM3��ʱ�� */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	 // GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
      
	  /* ����ʱ��3�Ĵ�����Ϊ��ʼֵ */
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
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
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
							  TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx����  
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


void TIM2_IRQHandler(void)   //TIM2�ж�,�̶ȼ�ʱ��
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			
			display_step++; 
			 if(display_step>360)
		 {
			 display_step=0;
		 }	
      		 
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		 TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
		    //�����ʾ��־λ
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


