`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.10.2021 20:40:51
// Design Name: 
// Module Name: ALU
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
`define ADD 5'b00000 
`define SUB 5'b01000
`define SLL 5'b00001
`define SLT 5'b00010
`define SLTU 5'b00011
`define XOR 5'b00100
`define SRL 5'b00101
`define SRA 5'b01101
`define OR 5'b00110
`define AND 5'b00111
`define BEQ 5'b11000
`define BNQ 5'b11001
`define BRLT 5'b11100
`define BRG 5'b11101
`define BRLU 5'b11110
`define BRGU 5'b11111

module ALU(
input [4:0] ALUop,
input [31:0] A,
input [31:0] B,
output reg [31:0] Result,

output reg  Flag
    );

always @(*) begin
    case(ALUop)
    `ADD:begin
        Result <= (A + B);
        Flag <= 0;
        end
        
    `SUB:begin
        Result <= (A - B);
        Flag <= 0;
        end  
     
    `SLL:begin
        Result <= (A << B);
        Flag <= 0;
        end
        
     `SLT:begin
        Result <= ($signed (A) < $signed (B));
        Flag <= 0;
        end
       
     `SLTU:begin
        Result <=  (A < B);
        Flag <= 0;
        end

     `XOR:begin
        Result <=  (A ^ B);
        Flag <= 0;
        end
       
     `SRL:begin
        Result <=  (A >> B);
        Flag <= 0;
        end
        
     `SRA:begin
        Result <=  (A >>> B);
        Flag <= 0;
        end

     `OR:begin
        Result <=  (A | B);
        Flag <= 0;
        end

     `AND:begin
        Result <=  (A & B);
        Flag <= 0;
        end
        
     `BEQ:begin
        Result <=  (A == B);
        Flag <= Result;
        end

     `BNQ:begin
        Result <=  (A != B);
        Flag <= Result;
        end
        
     `BRLT:begin
        Result <=  ($signed(A) < $signed(B));
        Flag <= Result;
        end 

     `BRG:begin
        Result <=  ($signed(A) >= $signed(B));
        Flag <= Result;
        end

     `BRLU:begin
        Result <=  !(A < B);
        Flag <= Result;
        end

     `BRGU:begin
        Result <=  (A >= B);
        Flag <= Result;
        end                           
    endcase
            end
endmodule
