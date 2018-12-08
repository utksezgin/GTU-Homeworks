module Mux_2x1(input_1, input_2, select, out);
input [31:0] input_1, input_2;
input select;
output [31:0] out;


	assign out 	= select==1'b0 ? input_1 : input_2;

endmodule