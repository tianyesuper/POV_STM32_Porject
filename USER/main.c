#include "sys.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"



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

//	
	    display_daa=0xff00;
        display_line(display_daa,display_daa,display_daa,display_daa);
        display_clear();
		while(1)
	    {
            
		 
 	      // DS1302_ReadTime(&Time_Structure);
 	       ifp= Remote_Process();   //红外接收到数据处理
        
	   	}
 }

