#ifndef __infrared_H
#define __infrared_H	 
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

//LED��������			 
//2012/2/27

//LED�˿ڶ���
  
#define RDATA PAin(1)	 //�������������
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      

extern u8 Remote_Cnt;    //��������,�˴ΰ��¼��Ĵ���
extern u8 Remote_Rdy;    //������յ����� 
extern u32 Remote_Odr;   //�����ݴ洦
u8 Remote_Process(void);   //������յ����ݴ���
u8 Pulse_Width_Check(void);//�������	 




#endif
