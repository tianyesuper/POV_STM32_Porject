#ifndef  __REVISION_H
#define  __REVISION_H

#ifdef  REVISION_GLOBALS//���÷��μ���֮ǰ���������
#define REVISION_EXT  
#else
#define REVISION_EXT  extern
#endif

#include "stm32f10x.h"
extern const  unsigned char cRevisionDate[12];
extern const  unsigned char cRevisionTime[16];


#endif

