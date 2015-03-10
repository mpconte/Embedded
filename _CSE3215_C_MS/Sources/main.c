/***********************************************************************************

  York University CSE3215
  Main.c
  Jan 09, 2006
  
***********************************************************************************/
#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */


#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

unsigned short int counter;  // unsigned 16-bit integer


void main(void)
{
  /* put your own code here */
  EnableInterrupts;  
  
  for(;;)
  {
          
    if (counter++ == 0)
      PORTA++;
    
    
    /* 
      DDRB=0xFF;
    
      PORTB=0x0F;
    */    
  }
}
