#include "sys.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"

extern u16 display_times;

int main(void)
 {
    u8 ifp=0;
    u16 display_times_buff=10,display_daa;
	   Hardware_Init();	    
      __enable_irq();      
      Beep_State(ENABLE);

//	Tasks_Init();

//	/* Start the scheduler. */
//	vTaskStartScheduler();

//	//if there is no statck space to create idle task ,it will enter here
//	while (1)
//	{
//		;
//	} 
//	
	    display_daa=0xff00;
        LED_Output ( ENABLE,  &display_daa);

		while(1)
	    {
            
		   if(display_times==0)
		   {
		       Timer_Update();
		   }
			 
           if(display_times_buff!=display_times)
           {
								display_times_buff=display_times;
			   
             //   LED_set_duty_singlechannel(LED0_ADDRESS,display_times_buff,display_times_buff+10);     
           }
        
 	      // DS1302_ReadTime(&Time_Structure);
 	       ifp= Remote_Process();   //红外接收到数据处理
        
	   	}
 }

