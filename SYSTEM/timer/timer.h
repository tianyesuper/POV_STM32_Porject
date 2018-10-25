#ifndef __TIMER_H
#define __TIMER_H	
#include "stm32f10x.h"


#define TIM2_ICPSC_DIV    0 //�ֱ���
#define TIM3_ICPSC_DIV   3  //�ֱ���
#define ERROR_TIME    10 //����ʱ��

typedef struct
{
	u16  cycle_time;    //��Ȧʱ��
	u16 scale_time;    //�̶�ʱ��
	u8  frequency;     //����Ƶ�� 

}Counter_TypeDef;


void Timer_init(void);
void Timer_Update(u16 Update_counter);
u16 Is_Timer_Update(u16 update_data);



#endif

