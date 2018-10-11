#ifndef  __REVISION_H
#define  __REVISION_H

#ifdef  REVISION_GLOBALS//该用法参见我之前发表的文章
#define REVISION_EXT  
#else
#define REVISION_EXT  extern
#endif

#include "stm32f10x.h"
extern const  unsigned char cRevisionDate[12];
extern const  unsigned char cRevisionTime[16];


#endif

