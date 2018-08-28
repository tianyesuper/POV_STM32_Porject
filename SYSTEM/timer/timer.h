#ifndef __TIMER_H
#define __TIMER_H	
#include "stm32f10x.h"

typedef struct
{
	unsigned char  cycle_time;    //��Ȧʱ��
	unsigned char  scale_time;    //�̶�ʱ��
	unsigned char  frequency;     //����Ƶ��     

}Counter_TypeDef;

void Timer_init(void);
void Timer_Update(void);



#endif

