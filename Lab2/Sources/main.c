/***********************************************************************************

Lab 2

Submitted by: Matthew Conte
              Usman Mahmood
  
***********************************************************************************/
#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */


#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

unsigned short int counter = 0;  // (25) unsigned 16-bit integer for counter

void main(void)
{

  // Port A and B are set for output
  DDRA = 0xFF;
  DDRB = 0xFF;
  
  EnableInterrupts;
  for(;;)
  { 
    // (25) - increment PORTA when 16-bit counter reaches 0
    if (counter == 0) {
      
      // (1) - Continually increment PORTA
      PORTA++;
      
      
      // Determining Truth Table (3)
      // Assign PORTA values from 0x00 to 0x07 to determine truth table
      // for all combinations of signals A,B,C for the Altera (one at a time
      // per program)
            
      /* PORTA =  0x00;     
         PORTA =  0x01;
         PORTA =  0x02;
         PORTA =  0x03;
         PORTA =  0x04;
         PORTA =  0x05;
         PORTA =  0x06; 
         PORTA =  0x07;
      */
    }
        
    
    
    // (25) increment 16-bit counter  
    counter = counter + 1;
    
       
       
    // PART B: Generating Required Time Signals   
    /*       
      Write 4-bit data (all 1's) from Dragon12's PORTB to Altera's Display
    
      PORTB=0x0F;
    */    
  } 
}
