#ifndef __beep_H
#define __beep_H	
#include "stm32f10x.h"
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//******************************************************************************** 
//不分频。PWM频率=72000/900=8Khz

//arr自动重装值
//psc时钟预分频数
#define ARR     900 
#define PSC     0 

void Beep_Configuration(void);
void Beep_State( FunctionalState  beepflag);



#endif
