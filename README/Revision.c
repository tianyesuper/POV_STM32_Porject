/****************************************Copyright (c)**************************************************
**                                                          ����&ѧ��
**                                      
**
**                          https://blog.csdn.net/weixin_40779546/article/details/81773697
********************************************************************************************************/

#define REVISION_GLOBALS
#include "revision.h"

 

const  unsigned char cRevisionDate[12] = __DATE__;
const  unsigned char cRevisionTime[16] = __TIME__;

 

//ÿ�α���keil����ʱ������ʱ��PC��ʱ�䶼�����ַ�����ģʽ��¼��cRevisionDate[12]��cRevisionTime[16]�У�ֻ����������´���Ĵ��뼴�ɣ�

 //sprintf((char *)firm_ware, "FirmWare = * 1.0 %s %s\r\n",  cRevisionTime, cRevisionDate);//��ȡ�汾��Ϣ  ��keil����ʱ�����

