#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "stm32f10x.h"
#include "EEPROM.h"
#include "led.h"
#include "timer.h"



void display_line(u16 display_data0,u16 display_data1,u16 display_data2,u16 display_data3);
void display_clear(void);
void display_ctrl(void);



#endif

