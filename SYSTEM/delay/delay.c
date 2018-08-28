#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/27
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
//////////////////////////////////////////////////////////////////////////////////	 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
#if SYSTEM_SUPPORT_OS
void delay_init(u8 SYSCLK)
{
	u32 reload;
	
//	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//ѡ���ⲿʱ��  HCLK
	fac_us=SYSCLK/1000000;		   //�����Ƿ�ʹ��OS,fac_us ����Ҫʹ��
	reload=SYSCLK/1000000;       //ÿ���ӵļ������� ��λΪM
	reload*=1000000/configTICK_RATE_HZ;     //����configTICK_RATE_HZ�������
	                                        //ʱ��reloadΪ24λ�Ĵ��������ֵ��
	                                        // 16777216����72M�£�Լ��0.233s����
	fac_ms=1000/configTICK_RATE_HZ;         //����OS������ʱ�����ٵ�λ
	SysTick->CTRL|=SysTick_CALIB_TICKINT_Msk;//����SYSTICK�ж�
	SysTick->LOAD=reload;                    //ÿ1/configTICK_RATE_HZ���ж�һ��
	SysTick->CTRL|=SysTick_CALIB_TICKINT_Msk;//����SYSTICK�ж�
}	 
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u32 nms)
{	 		
  if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)	//ϵͳ�Ѿ�����
	{
		if(nms>=fac_ms)
		{
			vTaskDelay(nms/fac_ms);         //FreeRTOS��ʱ

		}
		nms%=fac_ms;
	}
	delay_us((u32)(nms*1000));  	    
}   
//��ʱnms,���������������
//nms;Ҫ��ʱ��ms��   								   
void delay_xms(u32 nms)
{		
	u32 i;	    	 
		for(i=0;i<nms;i++) delay_us(1000);
}
#else
void delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}	

							    
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}   
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   


#endif

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
































