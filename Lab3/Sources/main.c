/***********************************************************************************

Lab 3

Submitted by: Matthew Conte
              Usman Mahmood
  
***********************************************************************************/
#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */

unsigned static char onset = 0;              // boolean flag if onset time trial
unsigned static char display = 0;            // boolean flag if foreground should display to 7-segment display
unsigned static int num_ms = 0;              // number of milliseconds that have passed
unsigned static char reaction_button = 0xFF; // 0xFF means it's NOT set to PTH pin of reaction button (SW2 or SW5)
                                             // otherwise, it's value is push button for reaction time  

// digit array to display numbers (and "E") on 7-segment LED
byte numbers[11] = {
0x3F, // 0 
0x06, // 1
0x5B, // 2
0x4F, // 3
0x66, // 4
0x6D, // 5
0x7D, // 6
0x07, // 7
0x7F, // 8
0x6F, // 9
0x79  // E
};

// 4 bytes for reaction time for each 7-segment display byte
byte reaction_time[4];


#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


  __interrupt void button_press(void) 
  {  
     // if interrupt is from SW3, enable onset trial
     if (PIFH == 0x04 && reaction_button == 0xFF) 
     {  
        PIFH = 0x04;  // Clear SW3 interrupt flag                        

        DDRP = 0x00;  // disable display on 7-segment display

        onset = 1;    // enable onset trial flag
        
        display = 0;  // disable display flag                   
     } 
     
     // if interrupt is from SW2 or SW5
     else if (PIFH == reaction_button) 
     {             
          PIFH = reaction_button; // clear SW flags
          reaction_button = 0xFF; // reset reaction_button                    
          
          DDRP = 0x0F;            // enable display on 7-segment display                 
          display = 1;            // enable display flag          
          
          // 1 digit
          if (num_ms < 10) 
          {
            reaction_time[0] = numbers[num_ms];
            reaction_time[1] = numbers[0];
            reaction_time[2] = numbers[0];
            reaction_time[3] = numbers[0];            
          } 
          
          // 2 digits
          else if (num_ms < 100) 
          {
            reaction_time[0] = numbers[(num_ms % 10)];
            reaction_time[1] = numbers[(num_ms / 10) % 10]; 
            reaction_time[2] = numbers[0];
            reaction_time[3] = numbers[0];         
          } 
          
          // 3 digits
          else if (num_ms < 1000)
          {
            reaction_time[0] = numbers[(num_ms % 10)];
            reaction_time[1] = numbers[(num_ms / 10) % 10];
            reaction_time[2] = numbers[(num_ms / 100) % 10];                                     ;
            reaction_time[3] = numbers[0];
          } 
              
          // 4 digits
          else if (num_ms < 9999)
          {
            reaction_time[0] =  numbers[(num_ms % 10)];
            reaction_time[1] =  numbers[(num_ms / 10) % 10];
            reaction_time[2] =  numbers[(num_ms / 100) % 10];
            reaction_time[3] =  numbers[(num_ms / 1000) % 10];              
          }      
     }               
  }    


  // occurs every 1 ms when TC0 interrupt is enabled
  __interrupt void ms_delay(void)   
  {                
      num_ms++;                  // increment num_ms      
      TFLG1 = 0x01;              // clear interrupt flag 
            
     // set reaction display to "E001" when num_ms = 9999 and 
     // onset trial has been done              
     if (num_ms >= 9999 && reaction_button != 0xFF) 
     {      
       reaction_time[0] = numbers[1];
       reaction_time[1] = numbers[0];
       reaction_time[2] = numbers[0];
       reaction_time[3] = numbers[10];
       display = 1;         
       reaction_button = 0xFF;
       DDRP = 0x0F;
     }
  }
 

void main(void)
{  
  // PORT H set for input
  DDRH = 0x00;  
  
  //enable PORT H SWx interrupts
  PIEH = 0x0F;
    
  // make switch buttons interrupt on rising edge          
  PPSH = 0x0F;  ;
                                
  // PORTB set for output               
  DDRB = 0xFF;
  PORTB = 0x00;  
     
  TSCR2 = 0x0D;    // disable TCNT overflow interrupt, prescale = 64       
                   // & reset TCNT on successful output compare 7 event
                   // (375 counts)
   
  TIOS = 0x08;   // TC7 as output compare
  TC7 = 375;     // 375 counts = 1 ms
  
  TIE = 0x08;    // enable TC7 interrupt 
    
  TSCR1 = 0x80;  // enable timer aka start incrementing TCNT  
    
    
  EnableInterrupts;
      
  for(;;)
  {                            
        // if SW3 is pushed, begin onset trial
       if (onset == 1) {
                     
          PORTB = 0x00;                                      
          num_ms = 0;                    
                                        
          // wait 500ms to 3000ms and pulse LED for 100ms here    
          if (TCNT <= 500) {           
            while (num_ms <= 500)
             if(num_ms == 400) {              
              PORTB=0x01;
              reaction_button = 0x01;
             }
          }
          else if (TCNT >= 3000) {         
            while (num_ms <= 3000)
              if(num_ms == 2900){                                
                PORTB=0x01;
                reaction_button = 0x01;                          
              }
          }
          else {           
            while (num_ms <= TCNT)          
              if(num_ms == TCNT-100) {                
                PORTB=0x80; 
                reaction_button = 0x08;
              }
          }     
          
          // Turn off all LEDs (flash off after 100ms)
          PORTB = PORTB - PORTB; 
                    
          // reset onset                          
          onset = 0;                
                    
          // reset num_ms and begin reaction timer after 100ms flash
          num_ms = 0;
       }
              
       // if display flag enabled, update 7-segment display with reaction time
       if (display == 1) 
       {
            PORTB = reaction_time[0];
            PTP = 0x07;          
                
            // wait 1ms
            num_ms = 0;
            while (num_ms < 2);
                
            PORTB = reaction_time[1];              
            PTP = 0x0B;          

           // wait 1ms
            num_ms = 0;
            while (num_ms < 2);

            PORTB = reaction_time[2];
            PTP = 0x0D;          

            // wait 1ms
            num_ms = 0;
            while (num_ms < 2);

            PORTB = reaction_time[3];          
            PTP = 0x0E;   
             
            // wait 1ms
            num_ms = 0;
            while (num_ms < 2);
       } 
  }   
}