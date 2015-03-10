
module fsm (c9, Reset, w, Pushn, Digit3, Digit2, Digit1, Digit0);
	input c9, w, Reset, Pushn, Reset;	
	output [6:0] Digit3, Digit2, Digit1, Digit0;
	wire LEDn;
	wire [6:0] Digit3, Digit2, Digit1, Digit0;
	wire ms_clock;	
	wire BCD0, BCD1, BCD2, BCD3;
	reg LED, onset, reaction;	
	
	
	// Instantiate our other modules
	ms_clock new_clock(c9, ms_clock);	
	BCDcount counter (c9, Reset, LED, BCD3, BCD2, BCD1, BCD0);
	seg7 seg3 (BCD3, Digit3);
	seg7 seg2 (BCD2, Digit2);
	seg7 seg1 (BCD1, Digit1);
	seg7 seg0 (BCD0, Digit0);	
	
	always @(posedge ms_clock)
	begin			
			if (onset)	
				begin
				onset=0; reaction = 1; //wait 500-3000 ms and flash LED for 100ms 
				end
			else if (reaction)										
				begin
				LED = 1; reaction = 0;//will enable display to 7-segment display					
				end
			else
				begin
				onset = 1; //enable onset trial				
				end					
				
 	end	 
 		
 
endmodule 
