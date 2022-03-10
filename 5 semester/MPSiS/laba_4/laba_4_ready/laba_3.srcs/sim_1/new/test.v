`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 28.10.2021 23:46:12
// Design Name: 
// Module Name: TBench
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


module test();
    reg clk;
    reg rst;

    wire [31:0] OUT;
 
    reg [31:0] IN;  

initial begin
    
	clk <= 1'b0;
	rst <= 1'b1;
	IN = 32'b00000000000000000000000000000001;
	forever #10 clk <= ~clk;	
end


always begin
	#100 rst <= 1'b0;
end	
          
          
arch dut(
    .IN(IN),
    .OUT(OUT),
    .rst(rst),
    .clk(clk)

    );  
            
        always @(posedge clk) begin
	if (rst) begin
	end else begin
		
				$display("[%0d] OUT: %d",$time,OUT);
	
	end
end    


endmodule