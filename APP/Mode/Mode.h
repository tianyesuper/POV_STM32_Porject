#ifndef __MODE_H
#define __MODE_H
#include "stm32f10x.h"
#include "EEPROM.h"
#include "led.h"
#include "timer.h"
#include "infrared.h"

#define READY      0X00
#define START      0X01 
#define CLOCK      0X02
#define PICTURE    0X03 
#define GAME       0X04 
#define END        0X05
#define OTHER      0X06




u8 display_mode(void);




#endif

