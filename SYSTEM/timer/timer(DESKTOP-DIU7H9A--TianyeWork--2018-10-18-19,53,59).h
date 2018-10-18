#ifndef __TIMER_H
#define __TIMER_H	
#include "stm32f10x.h"


#define RESOLUTION    1 //分辨率
#define ERROR_TIME    6 //错误时间

typedef struct
{
	u16  cycle_time;    //单圈时间
	u16 scale_time;    //刻度时间
	u8  frequency;     //计数频率 

}Counter_TypeDef;


void Timer_init(void);
void Timer_Update(void);
u16 Is_Timer_Update(u16 update_data);



#endif

