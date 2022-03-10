module RF(
    input clk,
    input rst,
    input [4:0] A1,
    input [4:0] A2,
    input [4:0] A3,
    input WE3, 
    input [31:0] WD3, 
    output reg [31:0] RD1,
    output reg [31:0] RD2
);

reg [31:0] RAM [0:31]; 
integer i;
always@* begin
RD1 <= (A1!=0) ? RAM[A1] : 32'b0;
RD2 <= (A2!=0) ? RAM[A2] : 32'b0;
end



always @(posedge clk) 
if (rst) begin
for( i = 0; i < 32 ; i = i + 1)
RAM[i] <= 1'b0;
end
else
if (WE3==1) RAM[A3]<= (A3!=0) ? WD3 : 32'b0;



endmodule