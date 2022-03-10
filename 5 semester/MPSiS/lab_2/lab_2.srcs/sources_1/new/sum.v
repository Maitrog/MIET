`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03.09.2021 16:39:42
// Design Name: 
// Module Name: sum_8
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

module sum (
    input a,
    input b,
    input cin,
    output s,
    output cout
);

wire p, g;

assign p=a^b;
assign g=a&b;
assign s=p^cin;
assign cout=g|(p&cin);
endmodule