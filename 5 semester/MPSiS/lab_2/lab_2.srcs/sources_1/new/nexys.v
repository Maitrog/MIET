`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01.10.2021 16:50:48
// Design Name: 
// Module Name: nexys
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


module nexys(
    input BTNL, BTNR, BTND, BTNU, BTNC,
    input [15:0] SW,
    output [15:0] LED
    );
    
    wire [4:0] ALUOp;
    assign ALUOp[0] = BTND;
    assign ALUOp[1] = BTNL;
    assign ALUOp[2] = BTNU;
    assign ALUOp[3] = BTNR;
    assign ALUOp[4] = BTNC;
    
    wire [31:0] A, B;
    reg [31:0] Result;
    reg Flag;
    genvar i;
    for(i = 0; i < 32; i = i+1) begin
        if(i < 24) begin
            assign A[i]=0;
            assign B[i]=0;
        end
        else begin
            assign A[i] = SW[i-24];
            assign B[i] = SW[i-16];
        end
    end
    
    generate 
        ALU new(
        .A(A),
        .B(B),
        .ALUOp(ALUOp),
        .Result(Result),
        .Flag(Flag)
        );
    endgenerate
    
    for(i = 0; i < 8; i = i+1) begin
        assign LED[i] = Result[i+24];
    end
    assign LED[15] = Flag;
endmodule
