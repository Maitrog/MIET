`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01.10.2021 14:59:50
// Design Name: 
// Module Name: sum_32
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


module sum_32(
        input [31:0] a,
        input [31:0] b,
        output [31:0] out
    );
    
    wire [32:0] c;
    
    assign c[0] = 0;
    genvar i;
    generate
        for(i=0; i<32; i=i+1) begin : newgen
            sum newsum(
                .a(a[i]),
                .b(b[i]),
                .cin(c[i]),
                .s(out[i]),
                .cout(c[i+1])
            );
            end
    endgenerate
endmodule

