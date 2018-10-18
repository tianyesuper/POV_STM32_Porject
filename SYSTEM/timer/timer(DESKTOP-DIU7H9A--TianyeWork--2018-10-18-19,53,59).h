#ifndef __TIMER_H
#define __TIMER_H	
#include "stm32f10x.h"


#define RESOLUTION    1 //�ֱ���
#define ERROR_TIME    6 //����ʱ��

typedef struct
{
	u16  cycle_time;    //��Ȧʱ��
	u16 scale_time;    //�̶�ʱ��
	u8  frequency;     //����Ƶ�� 

}Counter_TypeDef;


void Timer_init(void);
void Timer_Update(void);
u16 Is_Timer_Update(u16 update_data);



#endif

