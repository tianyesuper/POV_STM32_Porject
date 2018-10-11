#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/5/27
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.2修改说明
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
//////////////////////////////////////////////////////////////////////////////////	 
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数
//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
#if SYSTEM_SUPPORT_OS
void delay_init(u8 SYSCLK)
{
	u32 reload;
	
//	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//选择外部时钟  HCLK
	fac_us=SYSCLK/1000000;		   //不论是否使用OS,fac_us 都需要使用
	reload=SYSCLK/1000000;       //每秒钟的计数次数 单位为M
	reload*=1000000/configTICK_RATE_HZ;     //根据configTICK_RATE_HZ设置溢出
	                                        //时间reload为24位寄存器，最大值：
	                                        // 16777216，在72M下，约合0.233s左右
	fac_ms=1000/configTICK_RATE_HZ;         //代表OS可以延时的最少单位
	SysTick->CTRL|=SysTick_CALIB_TICKINT_Msk;//开启SYSTICK中断
	SysTick->LOAD=reload;                    //每1/configTICK_RATE_HZ秒中断一次
	SysTick->CTRL|=SysTick_CALIB_TICKINT_Msk;//开启SYSTICK中断
}	 
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u32 nms)
{	 		
  if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)	//系统已经运行
	{
		if(nms>=fac_ms)
		{
			vTaskDelay(nms/fac_ms);         //FreeRTOS延时

		}
		nms%=fac_ms;
	}
	delay_us((u32)(nms*1000));  	    
}   
//延时nms,不会引起任务调度
//nms;要延时的ms数   								   
void delay_xms(u32 nms)
{		
	u32 i;	    	 
		for(i=0;i<nms;i++) delay_us(1000);
}
#else
void delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}	

							    
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}   
//延时nus
//nus为要延时的us数.		    								   


#endif

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
































