#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//系统时钟初始化		   
//修改日期:2010/5/27
//版本：V1.4

//********************************************************************************  
void NVIC_Configuration(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

}
void GPIO_Configuration(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
   // GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
   // GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_14);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    LED_POWER =ENABLE;
		
}
void IWDG_Configuration(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) ;  //使能或者失能对寄存器IWDG_PR 和IWDG_RLR 的写操作 
    IWDG_SetPrescaler(IWDG_Prescaler_64);  //设置IWDG 预分频值，取值范围：4，8，16，32，64，128，256，最大为256
    while(IWDG_GetFlagStatus(IWDG_FLAG_PVU) == RESET) ; //预分频器更新中
    IWDG_SetReload(0x753);   //设置IWDG 重装载值   取值范围：0x00~0x0FFF
    IWDG_ReloadCounter();    //按照IWDG 重装载寄存器的值重装载IWDG 计数器 
    while(IWDG_GetFlagStatus(IWDG_FLAG_RVU) == RESET) ; //重装载值更新进行中
    IWDG_Enable();     //使能IWDG

/*喂狗时间计算公式，
Tout=((4*2^prer)*rlr)/40  单位ms（因为内部RC振荡不稳定，所以计算出来的喂狗时间也是个大概时间，不精确）
Tout：益出时间也就是至少多长时间喂狗一次
prer：分频系数0~7（低3位有效）
rlr：重装载寄存器值（低12位有效）
(4*2^prer)是分频系数值，即预分频值
如果配置预分频值为64，且3000ms左右喂狗一次，则可以计算出重装载寄存器值：3000=((4*2^4)*rlr)/40=64*rlr/40由此公式可以算出来寄存器值rlr＝1875，换算成16进制为0x753
*/

}



void Hardware_Init(void)
{
	   TIME_TypeDef Time_Structure;
			Time_Structure.sec=0;
			Time_Structure.min=0;
			Time_Structure.hour=21;
			Time_Structure.week=2;
			Time_Structure.date=14;
			Time_Structure.month=8;
			Time_Structure.year=18;
	
	   NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	   GPIO_Configuration();
	   Beep_Configuration();
       delay_init(72);	    	 //延时函数初始化	  
	   uart_init(115200);
	   IIC_Configuration();
	   LED_Init();			     //LED端口初始化
	   EXTIX_Init();
	   Timer_init();
	
	  DS1302_ReadTime(&Time_Structure);
    DS1302_SetupTime(&Time_Structure);    
}
void Tasks_Init(void)
{
	//  Task_LED_display_Init();
    //task_rotate_reset_init();
 //  Task_clock_work_Init();
//    Task_device_Ctrl_Init();
	
	
	
	
}
