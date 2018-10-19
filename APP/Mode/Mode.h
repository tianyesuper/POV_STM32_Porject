#ifndef __MODE_H
#define __MODE_H
#include "stm32f10x.h"
#include "EEPROM.h"
#include "led.h"
#include "timer.h"
#include "infrared.h"

//遥控器类型开关宏：1为正点原子遥控器，0为car遥控器。
#define COMPILE_INFR  1
#if COMPILE_INFR

#define UP        0X60
#define POWER     0XA2
#define PLAY      0X02 
#define ALIEN     0XE2
#define RIGHT     0XC2 
#define LEFT      0X22 
#define EIGHT     0X38
#define VOL_N     0XE0
#define DOWN      0XA8
#define VOL_P     0X90
#define ONE       0X68
#define TWO       0X98
#define THREE     0XB0
#define FOUR      0X30
#define FIVE      0X18
#define SIX       0X7A
#define SEVEN     0X10
#define NINE      0X5A
#define ZERO      0X42
#define DELETE    0X52

#else

#define CH_P       0XA2
#define CH         0X62 
#define CH_N       0XE2
#define LEFT       0X22 
#define RIGHT      0X02 
#define GO         0XC2
#define LESS       0XE0
#define ADD        0XA8
#define EQ         0X90
#define ZERO       0X68
#define HUNDRED    0X98
#define HUNDREDS   0XB0
#define ONE        0X30
#define TWO        0X18
#define THREE      0X7A
#define FOUR       0X10
#define FIVE       0X38
#define SIX        0X5A
#define SEVEN      0X42
#define EIGHT      0X4A
#define NINE       0X52


#endif

#define READY      0X00
#define START      0X01 
#define CLOCK      0X02
#define PICTURE    0X03 
#define GAME       0X04 
#define END        0X05
#define OTHER      0X06





u8 display_mode(void);




#endif

