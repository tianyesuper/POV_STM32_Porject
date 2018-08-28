#ifndef __TIMER_H
#define __TIMER_H	
#include "stm32f10x.h"

typedef struct
{
	unsigned char  cycle_time;    //单圈时间
	unsigned char  scale_time;    //刻度时间
	unsigned char  frequency;     //技术频率     

}Counter_TypeDef;

void Timer_init(void);
void Timer_Update(void);



#endif

