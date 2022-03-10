`timescale 1ns / 1ps

module data_memory(
    input clk,
    input [31:0] A,
    input WE,
    input [31:0] WD,
    output [31:0] RD
    );
    
    reg [31:0] mem [0:63]; //32x64
    
    assign RD = (A == 0)? 0 : mem[A];
    
    always @ (posedge clk)
        if (WE)
            begin 
                mem[A[7:2]] <= WD;//7-2+1=64
                $display($time, "!my logs: \t data_mem[%d]<-%d", A, WD);
            end
endmodule
