module mips_control(instruction, RegDst, Branch, MemRead, MemtoReg, AlluOp, MemWrite, AlluSrc, RegWrite, JumpReg, SignedOrNot);

input [31:0] instruction;
output RegDst, Branch, MemRead, MemtoReg, MemWrite, AlluSrc, RegWrite, JumpReg, SignedOrNot;
output [5:0] AlluOp; // Since we have 19 different instructions (11 R type and 18 others and we count R as 1 since we use function field for them)
	

	
	
		assign RegDst =( (instruction[31:26]==6'b000000 && instruction[5:0]== !(6'b001000) ) )? 1:0; //RegDst is only 1 for all the R type instructions except jr.
		assign JumpReg =( (instruction[31:26]==6'b000000 && instruction[5:0]== 6'b001000) || 	(instruction[31:26]==6'b000010) || (instruction[31:26]==6'b000011) ) ? 1:0; //Only 1 for jump instructions (j, jal, jr)
		assign Branch = ( (instruction[31:26]==6'b000100) || (instruction[31:26]==6'b000101)  ) ? 1:0;  //bne and beq
		assign MemRead = ( (instruction[31:26]==6'b100100) || (instruction[31:26]==6'b100101) ||(instruction[31:26]==6'b100011) ) ? 1:0;  //lbu, lhu, lw
		assign MemtoReg = ( (instruction[31:26]==6'b100100) || (instruction[31:26]==6'b100101) ||(instruction[31:26]==6'b100011) ) ? 1:0; //lbu, lhu, lw
		assign MemWrite = ( (instruction[31:26]==6'b101000) ||  (instruction[31:26]==6'b101001) || (instruction[31:26]==6'b101011) ) ? 1:0; //sb, sh, sw
		assign AlluSrc = ( (instruction[31:26]==6'b000000) || (instruction[31:26]==6'b000100) || (instruction[31:26]==6'b000101) ) ? 0:1; //If its R type or branch it has to be 0.
		assign RegWrite = ( (instruction[31:26]==6'b000100) || (instruction[31:26]==6'b000101)  ||  (instruction[31:26]==6'b000000 && instruction[5:0]== 6'b001000) || (instruction[31:26]==6'b000010) || (instruction[31:26]==6'b000011) || (instruction[31:26]==6'b101000) ||  (instruction[31:26]==6'b101001) || (instruction[31:26]==6'b101011)  ) ? 0:1; //It's 0 for the branch, jump and store instructions (beq, bne, j, jal, jr, sb, sh, sw)
		assign SignedOrNot = ( (instruction[31:26]==6'b001000	) || (instruction[31:26]==6'b001100) || (instruction[31:26]==6'b001111) || (instruction[31:26]==6'b001101) || (instruction[31:26]==6'b001010)) ? 1:0; //1 when instruction works on signed (addi, andi, lui, ori, slti)
		assign AlluOp =( (instruction[31:26]==6'b000000) ? 5'b00000
		:( (instruction[31:26]==6'b001000) ? 5'b00001
		:( (instruction[31:26]==6'b001001) ? 5'b00010
		:( (instruction[31:26]==6'b001100) ? 5'b00011
		:( (instruction[31:26]==6'b000100) ? 5'b00100
		:( (instruction[31:26]==6'b000101) ? 5'b00101
		:( (instruction[31:26]==6'b000010) ? 5'b00110
		:( (instruction[31:26]==6'b000011) ? 5'b00111
		:( (instruction[31:26]==6'b100100) ? 5'b01000
		:( (instruction[31:26]==6'b100101) ? 5'b01001
		:( (instruction[31:26]==6'b001111) ? 5'b01010
		:( (instruction[31:26]==6'b100011) ? 5'b01011
		:( (instruction[31:26]==6'b001101) ? 5'b01100
		:( (instruction[31:26]==6'b001010) ? 5'b01101
		:( (instruction[31:26]==6'b001001) ? 5'b01110
		:( (instruction[31:26]==6'b101000) ? 5'b01111
		:( (instruction[31:26]==6'b101001) ? 5'b10000
		:( (instruction[31:26]==6'b101011) ? 5'b10001
		:5'b00000)))))))))))))))))); //R-type instructions op code is 00000 others have their unique code
		
		
endmodule