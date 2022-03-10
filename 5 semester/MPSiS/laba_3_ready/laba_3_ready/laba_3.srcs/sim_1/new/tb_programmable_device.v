`timescale 1ns / 1ps

module tb_programmable_device();
reg clk;
reg reset;

arch arch(
	.clk(clk),
	.rst(reset)
);

initial begin
    clk = 1'b0;
    reset = 1;
    #20;
    reset = 0;
    $stop();
end

always #5 clk = ~clk;

endmodule
