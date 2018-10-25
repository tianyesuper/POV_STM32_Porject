#include  "display.h"
extern u16 display_step;
extern u16 IC2ReadValue;
extern u8 update;
u16 display_buff0[4]={0},display_buff1[4]={0};
u8  num_display[5][8]={
							{0x80,0x80,0x80,0x80,0xa1,0xff,0x81,0x80},//1
                            {0x80,0xa1,0xe3,0xc5,0xc9,0xb1,0x80,0x80},//2
							{0x3e,0x83,0x03,0x0e,0x05,0x83,0x45,0x39},//3
							{0x80,0x80,0xb1,0xc9,0xca,0xbc,0x80,0x80},//6
                            {0xb8,0xc4,0xc4,0x84,0xbc,0xc4,0xc4,0xb8},//9
					       };


void display_line(u16 display_data0,u16 display_data1,u16 display_data2,u16 display_data3)
{

    LED_Output ( DISABLE ,  &display_data3);
    LED_Output ( DISABLE,  &display_data2);
    LED_Output ( DISABLE,  &display_data1);
    LED_Output ( ENABLE,  &display_data0);

}
void display_clear(void)
{
   
    display_line(DISAPLAY_CLEAR_DATA ,DISAPLAY_CLEAR_DATA ,DISAPLAY_CLEAR_DATA ,DISAPLAY_CLEAR_DATA );
  
}
void display_ctrl(void)
{
    u16  data=0;
    static bool dispaly_state=DISAPLAY_GOING; 
    static u8 ram_state=DISAPLAY_RAM0;
    if (update)
        {
            data=Is_Timer_Update(IC2ReadValue);					  
          if(data)
          {
           
            Timer_Update(data);
          }
		   display_step=0;
           update=0;
           IWDG_FEED;
        }
   /*else
   {
		
	  if (data!=display_step)
		  {
		  data=display_step;
		  display_line(data,data,data,data);
		  }
       
   }         
      

}*/
 else
   {
		
	  if (data!=display_step&&dispaly_state==DISAPLAY_GOING)
		  {
		   data=display_step;

          if (ram_state==DISAPLAY_RAM0)
              {
              
               display_line(display_buff0[0],display_buff0[1],display_buff0[2],display_buff0[3]);
              }
          else
              {
               display_line(display_buff1[0],display_buff1[1],display_buff1[2],display_buff1[3]);
              }
		  
           dispaly_state=DISAPLAY_FINISH;
		  }
      if (dispaly_state==DISAPLAY_FINISH)
          {
           
            dispaly_state= display_ram(&ram_state);
          }
       
   }         



}
bool  display_ram(u8 *     qram)//DMA制定地址读取EEPROM进行复制操作

{
     bool  ram_state=DISAPLAY_FINISH;
   
        switch (*qram)
            {
            case DISAPLAY_RAM0:  
                if(display_step==0||display_step<6)       //2显示
                 {
                   display_buff0[3]= num_display[1][display_step];
            
                 }
                 if(display_step>86&&display_step<95)     //3显示
                 {
                       display_buff0[3]= num_display[2][display_step-87];
          
                 }   
                 if(display_step>177&&display_step<186) //6显示
                 {
                      display_buff0[3]= num_display[3][display_step-178];
                
                 }
                 if(display_step>266&&display_step<275) //9显示
                 {
                      display_buff0[3]= num_display[4][display_step-267];
             
                 }
                  if(display_step>351&&display_step<360)          //1显示
                 {
                   
                      display_buff0[3]= num_display[0][display_step-352];
             
                    }
								 else
								 {
									  display_buff0[3]=DISAPLAY_CLEAR_DATA;
								 }

                       *qram= DISAPLAY_RAM1;break;
            
            case DISAPLAY_RAM1:  
                if(display_step==0||display_step<6)       //2显示
                 {
                   display_buff0[3]= num_display[1][display_step];
            
                 }
                 if(display_step>86&&display_step<95)     //3显示
                 {
                       display_buff0[3]= num_display[2][display_step-87];
          
                 }   
                 if(display_step>177&&display_step<186) //6显示
                 {
                      display_buff0[3]= num_display[3][display_step-178];
                
                 }
                 if(display_step>266&&display_step<275) //9显示
                 {
                      display_buff0[3]= num_display[4][display_step-267];
             
                 }
                  if(display_step>351&&display_step<360)          //1显示
                 {
                   
                      display_buff0[3]= num_display[0][display_step-352];
             
                    }   
								 else
								 {
									  display_buff0[3]=DISAPLAY_CLEAR_DATA;
								 }
                    *qram= DISAPLAY_RAM0;break;
            
            default: ram_state=DISAPLAY_FINISH;
                     return ram_state;
            break;
            }

        ram_state=DISAPLAY_GOING;

    
    return ram_state;


}


