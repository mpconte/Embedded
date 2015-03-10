/***********************************************************************************

  York University CSE3215
  PreLab 6 - SPI Master
  
  Matthew Conte
  Usman Mahmood
  
***********************************************************************************/
#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */
//#include "DBug12.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

char temp;


// occurs on each DIP switch interrupt
__interrupt void dip_switched(void)
{

  PIFH = PTH;  //Clear Interrupt flags
		
	  		
   // Enable PORTPS outputs (with DDRS)
   // 0x80 = SS output
   // 0x40 = SCLK output
   // 0x20 = MOSI output
   
		
	// Send Data to Altera here
  
	DDRS = DDRS | 0x80;
		
	PTS = PTS | 0x80; // Bring SS high to deselect device
	SPI0DR = 0x00; // Write junk data to device (and start SCLK)
	
	while ((SPI0SR & 0x80) != 0x80); // Wait for transfer to finish 
	temp = SPI0DR; // Clear SPIF flag by reading data register
	
	PTS = PTS & ~0x80;      // Bring SS low to select slave
	SPI0DR = PTH; 		// send dip switch data to Altera
	
	while ((SPI0SR & 0x80) != 0x80); // Wait for transfer to finish 
	temp = SPI0DR; // Clear SPIF flag by reading data register
	PTS = PTS | 0x80; // Bring SS high to deselect device 




	// Read Data from Altera here
	
	DDRS = 0x00; // no SS output
	
	PTS = PTS & ~0x80; // Bring SS low to select device 

	SPI0DR = 0x00; // Write junk byte to device (and start SCLK)
	while ((SPI0SR & 0x80) == 0) ; // Wait for transfer to finish 
	PORTB = SPI0DR; // send received data to LED's 

	PTS = PTS | 0x80; // Bring SS high to deselect device 
	
}


void main(void)
{    
   // enable HCS12 as Master (enables SCLK output)
   SPI0CR1_MSTR = 1;

  
   // enable interrupt (SPIF) when SPI receives/transmits last SCK edge in data
   // transfer operation
   //SPI0CR1_SPIE = 1;
     
   // first SCLK edge is issued at the start of 8-cycle transfer operation
   SPI0CR1_CPHA = 1;


   // Bidirectional pin mode enabled  
   // SCK output   	     enabled (since MSTR = 1)
   //SPICR2_SPC0 = 1;	
   
   // SS output enabled
   //SPICR2_MODFEN = 1;
   //SPICR1_SSOE = 1
   
   
   // Enable SPI system
   SPI0CR1_SPE = 1;


  SPI0BR = 0xFF; // 3Mhz SCLK 


   // enable DIP switch interrupt
   PIEH = 0xFF; 
   
   // enable LED's as output
   DDRB = 0xFF;		     
  		  
   
   
   EnableInterrupts;
     
   for (;;)
   {
   }
}
