`timescale 1ns / 1ps

module ALU(
    input [4:0] ALUop,
    input [31:0] A,
    input [31:0] B,
    output reg [31:0] Result,
    output reg Flag
);

`define ADD 5'b00000
`define SUB 5'b01000
`define LDSh 5'b00001 //left double shift <<
`define SMALLER 5'b00010
`define uSMALLER 5'b00011
`define XOR 5'b00100
`define RDSh 5'b00101
`define RTSh 5'b01101 //right triple shift
`define OR 5'b00110 
`define AND 5'b00111 

`define DEqual 5'b11000 //==
`define NEqual 5'b11001 //!=
`define ISLESS 5'b11100 //<
`define GRorEQ 5'b11101 //>=
`define uISLESS 5'b11110 //unsigned(<)
`define uGRorEQ 5'b11111 //unsigned(>=)



always @ (*) begin
    Result = 32'b0;
    Flag = 1'b0;

	case (ALUop)
		`ADD:	Result <= A + B;
		`SUB:	Result <= A - B;
		`LDSh:	Result <= A << B;
		`SMALLER:	Result <= A < B;
		`uSMALLER:	Result <= $unsigned(A < B);
		`XOR:	Result <= A ^ B;
		`RDSh:	Result <= A >> B;
		`RTSh:	Result <= $signed(A) >>> $signed(B);
		`OR:	Result <= A | B;
		`AND:	Result <= A & B;
		
		`DEqual:	Flag <= A == B;
		`NEqual:	Flag <= A != B;
		`ISLESS:	Flag <= $signed(A) < $signed(B);
		`GRorEQ:	Flag <= $signed(A) >= $signed(B);
		`uISLESS:	Flag <= $unsigned(A < B);
		`uGRorEQ:	Flag <= $unsigned(A > B);
		
		default: Flag <= 0;
	endcase
end


endmodule 
