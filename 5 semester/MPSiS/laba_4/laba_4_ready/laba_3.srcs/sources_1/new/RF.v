`timescale 1ns / 1ps

module RF(
    input clk,
    input [4:0] A1,
    input [4:0] A2,
    input [4:0] A3,
    input WE3,
    input [31:0] WD3,
    input Reset,
    output [31:0] RD1,
    output [31:0] RD2
    );
    
    reg [31:0] Reg [0:31];
    
    assign RD1 = (A1 == 0)? 0:Reg[A1];
    assign RD2 = (A2 == 0)? 0:Reg[A2];
    
    integer i;
    always @ (posedge clk)
     if (WE3)
        begin 
            Reg[A3] <= WD3;
            $display($time, "!my logs: \t reg[%d]<-%d", A3, $signed(WD3));
        end
        
     else if(Reset)
         for(i = 0; i < 32; i=i+1)
             Reg[i] = 0;
        
endmodule
