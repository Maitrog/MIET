`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 28.10.2021 21:06:45
// Design Name: 
// Module Name: SHELL
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


module arch(
    input clk,
    input rst,
    input [31:0] IN,
    output [31:0] OUT
    );
wire [31:0] instr;   

mem mem_connection(
.clk (clk),
.A(PC),
.RD(instr)
);

always @(posedge clk ) 
begin
    if (rst==1)
    PC <=8'b0;
    else begin
         	case(B | (C && Flag))
            	2'b00 : 
            	       PC <= PC + 8'b00000001;
            	2'b01 : 
            	   //if (Result != 0)
            	       PC <= PC + const;
            	   //else
            	       //PC <= PC + 8'b00000001;          	       
         	endcase
    	end
end
    
wire B; assign B = instr[31];
wire C; assign C= instr[30];
wire WE; assign WE = instr[29]|instr[28];
wire [1:0] WS; assign WS = instr[29:28];
wire [4:0] ALUop; assign ALUop = instr[27:23];
wire [4:0] RA1; assign RA1 = instr[22:18];
wire [4:0] RA2; assign RA2 = instr[17:13];
wire [7:0] const; assign const = instr[12:5];
wire [4:0] WA; assign WA = instr[4:0];


reg [31:0] WD=0;
wire [31:0] Result; 

wire [31:0] RD2;
wire [31:0] RD1;
wire Flag;
reg [7:0] PC=0;
assign OUT = RD1;







always @(*) 
begin
    if (WE) begin
                case(WS)
                     2'b01: WD = IN;
                     2'b10 : WD <= {{24{instr[12]}}, instr[12:5]};
                     2'b11: WD = Result;
                endcase
            end
end
RF RF_connection(
.clk(clk),
.A1(RA1),
.A2(RA2),
.A3(WA),
.RD1(RD1),
.RD2(RD2),
.WD3(WD),
.WE3(WE),
.rst (rst)
);

ALU ALU_connection(
.ALUop(ALUop),
.A(RD1),
.B(RD2),
.Result(Result),
.Flag(Flag)
);
endmodule
