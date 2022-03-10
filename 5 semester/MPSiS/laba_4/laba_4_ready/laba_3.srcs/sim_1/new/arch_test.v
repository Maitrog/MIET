`timescale 1ns / 1ps

module arch_test();
    reg clk;
    reg reset;

arch arch_tb(
	.clk(clk),
	.reset(reset)
);

initial begin
    //clk = 1'b0;
    //reset = 1;
    //#20;
    //reset = 0;
    //wait(arch_tb.pc_adr == 76);
    //$stop();
    //clk <= 1'b0;
	//reset <= 1'b1;
	clk = 1'b0;
    reset = 1;
    #20;
    reset = 0;
    //wait(programmable_device_add.pc_adr == 76);
    $stop();
end

always #5 clk = ~clk;

endmodule
