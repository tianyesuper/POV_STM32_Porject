#include  "display.h"
extern u16 display_times;
extern u16 IC2ReadValue;
extern u8 update;

void display_line(u16 display_data0,u16 display_data1,u16 display_data2,u16 display_data3)
{

    LED_Output ( DISABLE ,  &display_data3);
    LED_Output ( DISABLE,  &display_data2);
    LED_Output ( DISABLE,  &display_data1);
    LED_Output ( ENABLE,  &display_data0);




}
void display_clear(void)
{
   
    u16 display_clear_data=0x0000; 
    display_line(display_clear_data,display_clear_data,display_clear_data,display_clear_data);

 
  
}
void display_ctrl(void)
{
    u16  data=0;
    if (update)
        {
            data=Is_Timer_Update(IC2ReadValue);
					  
          if(data)
             Timer_Update(data);
					 display_times=0;
        }
     
    
      /*     if(display_times==0)
             {
                 Timer_Update();
             }
               
             if(display_times_buff!=display_times)
             {
                                  display_times_buff=display_times;
                 
               //   LED_set_duty_singlechannel(LED0_ADDRESS,display_times_buff,display_times_buff+10);     
             }
          

*/


}


