#include "mode.h"

u8 display_mode(void)
{
   static u8 mode_state=READY;
    switch(mode_state)
    {
        case READY: break;
                           
        case START:break;
                            
        case CLOCK:break;
                            
        case PICTURE:break;
                                                     
        case GAME:break;
                                     
        case END: break;
                                                               
        default:

                      break;


    }
    
    return mode_state;

}


