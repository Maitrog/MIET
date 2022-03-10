`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 28.10.2021 22:05:18
// Design Name: 
// Module Name: IM
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


module mem(
    input clk,
    input [31:0] pc_adr,
    output reg [31:0] rd //read data
    );
    
//    reg [31:0] mem[0:255];
    
//    assign rd = mem[pc_adr[9:2]]; 
    
//    initial $readmemh("mem.mem", mem);
//    input clk,
    
//    input [7:0] A,
//    output reg [31:0] RD
//    );
    
    reg [31:0] memory[0:255];
    
    initial $readmemh("memory.mem", memory);
    
    always @ (negedge clk) begin
    rd <= memory[pc_adr[9:2]];
    end
endmodule
