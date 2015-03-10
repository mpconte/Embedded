/***********************************************************************************

  York University CSE3215
  Main.c
  Jan 09, 2006
  
***********************************************************************************/
#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */


#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


__interrupt void RealTimeInterrupt(void);
 

static volatile unsigned char rtiCnt;        /* to count number of RTIs */
static unsigned char voltage; 
static unsigned char temp;
static unsigned char max_8 = 0b11111111;


// digit array to display numbers on 7-segment LED
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
 
void main(void)
{
  /* set up Port B */
  DDRB = 0xFF;                /* set portb pins all to output */
  PORTB = 0x00;         /* turn Port B LEDs off */
  
  DDRP = 0xFF;
 
  /* Set up the A/D converter and start it running; we use 8 bit resolution.*/
  ATD0CTL2 = 0x80;      /* turn on ADC */
  ATD0CTL3 = 0x08;      /* 1 AD conversion/sequence */
  ATD0CTL4 = 0xEB;      /* 8 bit, 16 AD clocks/conversion, 1 MHz clock */
  ATD0CTL5 = 0x27;   /* left justify, unsigned, sample only specified channel */
 
  /* set up RTI */
  RTICTL = 0x31;            /* (2*2^12)/(4x10^6) = 2.048 ms per RTI */
  CRGINT |= 0x80;            /* enable RTI interrupt */
  rtiCnt = 0;                /* RTI counter to 0 */
  
  EnableInterrupts; 
  
  for (;;) {                /* our infinite loop */
 
    if (rtiCnt == 2)      /* check the AD registers every 10 msec */
    { 
      /* light LEDs according to range in AD result register; since 8 bit,
      *  we need only to look at the high byte, ATD0DR0H, of the result register*/
 
 /*
      if(ATD0DR0H <= 0x20)  
       PORTB = 0x00;
      if(ATD0DR0H > 0x20)
       PORTB = 0x01;
      if(ATD0DR0H > 0x40)
       PORTB = 0x03;
      if(ATD0DR0H > 0x60)
       PORTB = 0x07;
      if(ATD0DR0H > 0x80)
       PORTB = 0x0f;
      if(ATD0DR0H > 0xa0)
       PORTB = 0x1f;
      if(ATD0DR0H > 0xc0)
       PORTB = 0x3f;
      if(ATD0DR0H > 0xe0)
       PORTB = 0x7f;
      if(ATD0DR0H == 0xff)   
       PORTB = 0xff;
          */       
       
       //Display actual voltage to 7-segment display          
          
       voltage =  (char) ((0b00000101 * ATD0DR0H) / max_8);
       temp = voltage / 0b00001010;

       PORTB = numbers[voltage % 0b00001010];
       PTP = 0x07;
       
       /*
       rtiCnt = 0;
       while ( rtiCnt <= 1);             
              
       PORTB = numbers[(voltage / 10) % 10];
       PTP = 0x0B;
       
       rtiCnt = 0;
       while ( rtiCnt <= 1);             
       
       PORTB = numbers[(voltage / 100) % 10];
       PTP = 0x0D;      
                     */
       rtiCnt = 0;
    }
  }
} /* end main() */
 
   
__interrupt void RealTimeInterrupt(void)
{
  rtiCnt++;                    /* increment counter        */
  CRGFLG = 0x80;            /* clear rti flag               */
} 
 