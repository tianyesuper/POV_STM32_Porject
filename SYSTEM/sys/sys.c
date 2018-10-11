#include "sys.h"
#include "DS1302.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ϵͳʱ�ӳ�ʼ��		   
//�޸�����:2010/5/27
//�汾��V1.4

//********************************************************************************  
void NVIC_Configuration(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

}
void GPIO_Configuration(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP��
   // GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    // �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��
   // GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_14);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    POWER =1;
	
	
	
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
	
	   NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	   GPIO_Configuration();
	   Beep_Configuration();
     delay_init(72);	    	 //��ʱ������ʼ��	  
	   uart_init(115200);
	   IIC_Configuration();
	   LED_Init();			     //LED�˿ڳ�ʼ��
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
