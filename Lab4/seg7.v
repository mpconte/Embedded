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
