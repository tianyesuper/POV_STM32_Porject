#ifndef __beep_H
#define __beep_H	
#include "stm32f10x.h"
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//******************************************************************************** 
//����Ƶ��PWMƵ��=72000/900=8Khz

//arr�Զ���װֵ
//pscʱ��Ԥ��Ƶ��
#define ARR     900 
#define PSC     0 

void Beep_Configuration(void);
void Beep_State( FunctionalState  beepflag);



#endif
