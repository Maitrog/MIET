`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01.10.2021 15:25:51
// Design Name: 
// Module Name: invert_32
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


module invert_32(
    input [31:0] A,
    output [31:0] invA
    
    genvar i
    for(i=0; i < 32; i++)begin 
        invA[i] = A
    
    );
endmodule
