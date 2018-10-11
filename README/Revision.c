/****************************************Copyright (c)**************************************************
**                                                          他乡&学子
**                                      
**
**                          https://blog.csdn.net/weixin_40779546/article/details/81773697
********************************************************************************************************/

#define REVISION_GLOBALS
#include "revision.h"

 

const  unsigned char cRevisionDate[12] = __DATE__;
const  unsigned char cRevisionTime[16] = __TIME__;

 

//每次编译keil工程时，编译时的PC机时间都会以字符串的模式记录到cRevisionDate[12]和cRevisionTime[16]中，只需再添加如下处理的代码即可：

 //sprintf((char *)firm_ware, "FirmWare = * 1.0 %s %s\r\n",  cRevisionTime, cRevisionDate);//获取版本信息  与keil编译时间相关

