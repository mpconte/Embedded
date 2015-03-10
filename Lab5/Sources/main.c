/***********************************************************************************

  York University CSE3215
  Main.c
  Jan 09, 2006
  
***********************************************************************************/
#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


static unsigned int rtiCnt;        /* to count number of RTIs */
static unsigned char max_8 = 0b11111111;

static unsigned char voltage;
static unsigned char temp;

static unsigned char set_point_voltage;
static unsigned char set_point_temp;

static char num_display_updates = 10;


// digit array to display numbers (and .) on 7-segment LED
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
0x80  // .
};

__interrupt void RealTimeInterrupt(void)
{
  rtiCnt++;                    // increment the counter       
  CRGFLG = 0x80;               // clear rti flag               
}

__interrupt void conversion_complete(void) 
{
/*
   set_point_voltage =  (char) ((0b00000101 * ATD0DR0H) / max_8);
   set_point_temp = set_point_voltage / 0b00001010;
   
   PORTB = numbers[set_point_voltage % 0b00001010];               
   PTP = 0x0D;
            
   ATD0CTL5 = 0x26; // read Analog signals from channel 6 again  
   
   num_display_updates = 0;
   */
}


void main(void)
{ 
   DDRB = 0xFF;   

  // Step 1:  
  ATD0CTL2 = 0x80; // Power up A/D (|= 0x02 enables interrupt of ATD conversion sequence)
  ATD0CTL3 = 0x40; // Eight conversions
  ATD0CTL4 = 0x82; // 8-bit mode, 3MHz ATD conversion clock (could interrupt here)
  ATD0CTL5 = 0x27;    /* 1 0 1 0 0 1 1 0
                                   \___/
                                    |
                                    |
                                     \_ Channel x of Port AD
                                   
                    */  
 
 
 // Convert digital code from ATD0DR0 into Voltage then into Degrees (C)
 //  actual_voltage = (44*ATD0DR0)/(0b1111111111)
 //  acutal_temp = actual_voltage / 0b1010;
        
        
        
  // Step 2:
  
  // enable PWM channel 7 output
  PWME_PWME7 = 1;
  
  // assign PWM channel 7 to use clock SB
  PWMCLK_PCLK7 = 1;
  
  PWMPRCLK = 0x70; //prescale clock B by 128 (B = B / 128 = 24MHz / 128 = 187.5 KHz)       

  PWMSCLB = 0; // PWMSCLB = 0 => SB = B / 512 => 187.5 KHz / 512 = 366.2 Hz
               // Period = 1 / 366.2 Hz = 2.7 ms
  
  PWMPER7 = 3; // PWM Channel 7 period = (2.7ms * 3) = 8.2 ms

  //PWMDTY7 = 0; // PWM duty cycle = (PWMPER7-PWMDTY7)/PWMPER7 * 100%





  // Set up RTI ms counter here    
  RTICTL = 0x31;            // (2*2^12)/(4x10^6) = 2.048 ms per RTI
  CRGINT |= 0x80;            // enable RTI interrupt
  rtiCnt = 0;                // RTI counter to 0 
      
    
  EnableInterrupts;
  
  for(;;)
  {    
    // 1) check AD registers every 10 ms
    // 2) after 100 ms, initiate ATD conversion on channel 7 (input from VR2), and interrupt 
    //    upon completion
    if (rtiCnt == 5) 
    {    
          num_display_updates++;
          
          voltage =  (char) ((0b00000101 * ATD0DR0H) / max_8);
          temp = voltage / 0b00001010;

          
          // Update display of actual temperature
          rtiCnt = 0;
          while (rtiCnt <= 2);

          PORTB = numbers[voltage % 0b00001010];
          PTP = 0x07;         
          
          /*
          rtiCnt = 0;
          while (rtiCnt <= 2);

          PORTB = numbers[(voltage/0b00001010) % 0b00001010];
          PTP = 0x0B;                                        
            */
          
           /*
          if (num_display_updates == 10) 
          {
            ATD0CTL5 = 0x27;  // read from ATD channel 7 (VR2 output)
            ATD0CTL2 |= 0x02; // enable conversion sequence interrupt

            while (!ATD0STAT0_SCF); // wait until conversion sequence is complete
                                    // and then determine value at channel 7                                                                                                                 
          }
          */
    }                    
  }
}
