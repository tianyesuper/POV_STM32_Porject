#include "timer.h"
//time2��ʱ��
//time3������
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!



void Timer_init(void)
{
     
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


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

	/* ����TIM3��ʱ�� */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	  
	  /* ����ʱ��3�Ĵ�����Ϊ��ʼֵ */
	  TIM_DeInit(TIM3);
	  
	  /* ���ö�ʱ��3���ڲ�ʱ�� */
	//  TIM_InternalClockConfig(TIM3);
	  
	  /* Ԥ��Ƶֵ */
	  TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1;
	  /* ʱ�ӷָ� */
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	  /* ���ϼ��� */
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  /* �Զ�����ֵ */
	  TIM_TimeBaseStructure.TIM_Period = 0;
	  /* ��ʼ����ʱ��2 */
	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	  
	  /* �������жϱ�־ */
	  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	  
	  /* ��ֹARRԤװ�ػ����� */
	  TIM_ARRPreloadConfig(TIM3, ENABLE);
	  
	  /* ����TIM2���ж� */
	  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	  
	  /* ������ʱ��2 */
	  TIM_Cmd(TIM3, ENABLE);




}



void TIM2_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		//�����ʾ��־λ
		}
}



