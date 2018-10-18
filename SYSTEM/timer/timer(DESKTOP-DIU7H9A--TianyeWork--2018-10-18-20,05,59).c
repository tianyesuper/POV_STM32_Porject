#include "timer.h"
//time2��ʱ��
//time3������
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
u32 Freq;
u16 display_times=10;
u16 IC2ReadValue=0;
u8 update=0;
void Timer_init(void)
{
     
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
    TIM_DeInit(TIM2);

	TIM_TimeBaseStructure.TIM_Period = 5000; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���¼���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ARRPreloadConfig(TIM2, ENABLE); //����ARRԤװ�ػ�����
    
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
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
      
	  /* ����ʱ��3�Ĵ�����Ϊ��ʼֵ */
	   TIM_DeInit(TIM3);
		 
	   
		 
		  TIM_ICInitStructure.TIM_Channel	  = TIM_Channel_2;
		  TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
		  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
		  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		  TIM_ICInitStructure.TIM_ICFilter	  = 0x0;
	  
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
		  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
	
}

void Timer_Update(u16 Update_counter       )
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx����  
	if()
	TIM_TimeBaseStructure.TIM_Period = Update_counter; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	else
	TIM_TimeBaseStructure.TIM_Prescaler =1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����

}
u16 Is_Timer_Update(u16 update_data)
{
    static u16   IC2ReadValue1=0, IC2ReadValue2=0;
     update=0;
       
            /* Get the Input Capture value */
            IC2ReadValue2 = update_data;

            
           
            if(((IC2ReadValue2-IC2ReadValue1)>ERROR_TIME)||((IC2ReadValue2-IC2ReadValue1)>ERROR_TIME))
             {

                   circle_counter=IC2ReadValue2/RESOLUTION/360;                
                
            }
            else 
            {
                 circle_counter=0;                 
            }
            
            IC2ReadValue1=IC2ReadValue2;
        return circle_counter;


}


void TIM2_IRQHandler(void)   //TIM2�ж�
{	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		
			display_times++;
				if(display_times==360)
				{
				   display_times=0;
				   //Timer_Update_flag=SET;
				   TIM2->ARR=circle_counter/360/RESOLUTION ;
				}
		 TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		           //�����ʾ��־λ
		}
}

void TIM3_IRQHandler(void)
{ 
    update=1;

    if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) 
    {
        /* Clear TIM2 Capture compare interrupt pending bit */
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
        IC2ReadValue= TIM_GetCapture2(TIM3);
    }
}


