`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01.10.2021 15:15:01
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
//////////////////////////////////////////////////////////////////////////////////



module ALU(
    input [4:0] ALUOp,
    input [31:0] A,
    input [31:0] B,
    output reg [31:0] Result,
    output reg Flag
    );
    
    
    always @(*) begin
        case(ALUOp)
        5'b00000: begin 
        Result = A+B;
        Flag = 0;
        end
        5'b01000: begin 
        Result = A-B;
        Flag = 0;
        end
        5'b00001: begin 
        Result = A << B;
        Flag = 0;
        end
        5'b00010: begin 
        Result = ($signed(A) < $signed(B)) ? 1 : 0;
        Flag = 0;
        end
        5'b00011: begin 
        Result = ($unsigned(A) < $unsigned(B))? 1 : 0;
        Flag = 0;
        end
        5'b00100: begin 
        Result = A ^ B;
        Flag = 0;
        end
        5'b00101: begin 
        Result = A >> B;
        Flag = 0;
        end
        5'b01101: begin 
        Result = A >>> B;
        Flag = 0;
        end
        5'b00110: begin 
        Result = A | B;
        Flag = 0;
        end
        5'b00111: begin 
        Result = A & B;
        Flag = 0;
        end
        5'b11000: begin 
        Result = ($signed(A) == $signed(B)) ? 1 : 0;
        Flag = ($signed(A) == $signed(B)) ? 1 : 0;
        end
        5'b11001: begin 
        Result = ($signed(A) != $signed(B)) ? 1 : 0;
        Flag = ($signed(A) != $signed(B)) ? 1 : 0;
        end
        5'b11100: begin 
        Result = ($signed(A) < $signed(B)) ? 1 : 0;
        Flag = ($signed(A) < $signed(B)) ? 1 : 0;
        end
        5'b11101: begin 
        Result = ($signed(A) >= $signed(B)) ? 1 : 0;
        Flag = ($signed(A) >= $signed(B)) ? 1 : 0;
        end
        5'b11110: begin 
        Result = ($signed(A) < $signed(B)) ? 1 : 0;
        Flag = ($signed(A) < $signed(B)) ? 1 : 0;
        end
        5'b11110: begin 
        Result = ($unsigned(A) < $unsigned(B)) ? 1 : 0;
        Flag = ($unsigned(A) < $unsigned(B)) ? 1 : 0;
        end
        5'b11111: begin 
        Result = ($unsigned(A) >= $unsigned(B)) ? 1 : 0;
        Flag = ($unsigned(A) >= $unsigned(B)) ? 1 : 0;
        end
        endcase
    end
endmodule
