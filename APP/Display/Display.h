#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "stm32f10x.h"
#include "EEPROM.h"
#include "led.h"
#include "timer.h"
#include <stdbool.h>

#define DISAPLAY_CLEAR_DATA    (u16)0x0000
#define DISAPLAY_FINISH         (bool) 0
#define DISAPLAY_GOING          (bool) 1
#define DISAPLAY_READY          1
#define DISAPLAY_NOREADY        0
#define DISAPLAY_RAM0           0
#define DISAPLAY_RAM1           1




void display_line(u16 display_data0,u16 display_data1,u16 display_data2,u16 display_data3);
void display_clear(void);
void display_ctrl(void);
bool  display_ram(u8 *  qram);


#endif

