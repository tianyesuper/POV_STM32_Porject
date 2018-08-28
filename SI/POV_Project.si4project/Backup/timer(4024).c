#include "timer.h"
//time2��ʱ��
//time3������
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
u32 Freq;


void Timer_init(void)
{
     
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = 5000; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
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


void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		//�����ʾ��־λ
		}
}

void TIM3_IRQHandler(void)
{ 
    static u16   Capture, IC2ReadValue1, IC2ReadValue2;
    static u8    CaptureNumber = 0;
    
    if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) 
    {
        /* Clear TIM2 Capture compare interrupt pending bit */
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
        if(CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC2ReadValue1 = TIM_GetCapture2(TIM3);
            CaptureNumber = 1;
        }
        else if(CaptureNumber == 1)
        {
            /* Get the Input Capture value */
            IC2ReadValue2 = TIM_GetCapture2(TIM3); 

            /* Capture computation */
            if (IC2ReadValue2 > IC2ReadValue1)
            {
                Capture = (IC2ReadValue2 - IC2ReadValue1); 
            }
            else
            {
                Capture = ((0xFFFF - IC2ReadValue1) + IC2ReadValue2); 
            }
            /* Frequency computation */ 
            Freq = (u32) SystemCoreClock / Capture;
            CaptureNumber = 0;
        }
    }
}


