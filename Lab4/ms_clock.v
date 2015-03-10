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
		
		if (counter == 13500) //13500 counts == half a period (0.5 ms)
		begin
			newClock = ~newClock; // switch ms clock
			counter = 8'd0;       // reset counter
		end
	end		
endmodule
