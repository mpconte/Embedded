module ms_clock(Clock, newClock);
	input Clock;
	output newClock;
	
	wire Clock;
	reg newClock;	
	reg[7:0] counter;
 	
	initial begin
		counter = 8'd0;  // ms counter is 0 at first
		newClock = 1'b0; // ms clock is low at first
	end
 
 	always @(posedge Clock)
	begin
		
		counter = counter + 8'd1;
		
		if (counter == 2) //13500 counts == half a period (0.5 ms)
		begin
			newClock = ~newClock; // switch ms clock
			counter = 8'd0;       // reset counter
		end
	end		
endmodule



module seg7 (bcd, leds);
	input [3:0] bcd;	
	output [6:0] leds;		
	
	wire [3:0] bcd;
	reg [6:0] leds;	

	always @(bcd)	
	begin
		case (bcd)       
			0: leds = 7'b1111110;
	   	1: leds = 7'b0110000;
			2: leds = 7'b1101101;
			3: leds = 7'b1111001;
			4: leds = 7'b0110011;
			5: leds = 7'b1011011;
			6: leds = 7'b1011111;
			7: leds = 7'b1110000;
			8: leds = 7'b1111111;
			9: leds = 7'b1111011;
			default: leds = 7'b0000000;
		endcase	
	end	
	
endmodule



module BCDcount (Clock, Clear, E, BCD3, BCD2, BCD1, BCD0);
	input Clock, Clear, E;
	output [3:0] BCD3, BCD2, BCD1, BCD0;	
	
	wire Clock, Clear, E;
	reg [3:0] BCD3, BCD2, BCD1, BCD0;						
	reg carry_flag;
	wire [6:0] LED0, LED1, LED2, LED3;
	wire newClock;
	
	seg7 seg(BCD0, LED0);
  seg7 seg(BCD1, LED1);
	seg7 seg(BCD2, LED2);
	seg7 seg(BCD3, LED3);
  ms_clock new_clock(Clock, newClock);
  	
	initial 
	begin
		  carry_flag = 0;
	    BCD3 = 0;
	    BCD2 = 0;
	    BCD1 = 0; 
	    BCD0 = 0;
	end
			
	always @(posedge newClock or posedge Clear)
	begin		
				
	    if (Clear)
	    begin
	    	BCD3 <= 0;
	    	BCD2 <= 0;
	        BCD1 <= 0; 
	        BCD0 <= 0;	        
	    end	   
        
	    else if (E)
	    
            if (BCD0 == 4'b1001)
       	  	  begin
	    		BCD0 <= 0;
	    		carry_flag = 1'b1;
			  end
			else
			  begin
			  	BCD0 <= BCD0 + 1'b1;
			  end
			
			if (carry_flag)
			begin
					if (BCD1 == 4'b1001)
					  begin
						BCD1 <= 0;					
					  end
					else
					  begin
						BCD1 <= BCD1 + 1'b1;
						carry_flag = 0;
					  end
							
														
						if (carry_flag)
						begin			
								if (BCD2 == 4'b1001)
								  begin
									BCD2 <= 0;
								  end
								else
								  begin
									BCD2 <= BCD0 + 1'b1;
									carry_flag = 0;
								  end
								
								
								if (carry_flag)
								begin
								
									if (BCD3 == 4'b1001)
									  begin
										BCD3 <= 0;
									  end
									else
									  begin
										BCD3 <= BCD0 + 1'b1;
										carry_flag = 0;
									  end  
								end
						end  
			end 					
				
		end										
		
endmodule