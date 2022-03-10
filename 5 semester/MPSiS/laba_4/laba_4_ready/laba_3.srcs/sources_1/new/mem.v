`timescale 1ns / 1ps

module mem(
    input clk,
    input [31:0] pc_adr,
    output reg [31:0] rd //read data
    );

    reg [31:0] memory[0:255];

    initial $readmemb("memory.mem", memory);

    always @ (negedge clk) begin
    rd <= memory[pc_adr[9:2]];
    end
endmodule

//    input clk,

//    input [7:0] A,
//    output reg [31:0] RD
//    );

//    reg [31:0] memory[0:255];

//    initial $readmemb("memory.mem", memory);

//    always @ (negedge clk) begin
//    RD <= memory[A];
//    end
//`timescale 1ns / 1ps

//module instructions_memory(
//    input [31:0] pc_adr,
//    output [31:0] rd //read data
//    );
    
//    reg [31:0] mem[0:255];
    
//    assign rd = mem[pc_adr[9:2]]; 
    
//    initial $readmemh("memory.mem", mem);

//endmodule