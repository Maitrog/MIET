module RFTEST();
    reg clk;
    reg rst;
    reg [5:0] A;
    reg [4:0] A1;
    reg [4:0] A2;
    reg [4:0] A3;
    reg WE3;
    reg [31:0] WD3;
    reg [31:0] IN;
    wire [31:0] RD;
    wire [31:0] RD1;
    wire [31:0] RD2;
    wire [31:0] OUT;
    
    
integer i;

always #5 clk = ~clk;

initial begin
    clk <= 1'b0;
    rst <= 1'b1;
    A <= 5'b00001;
    A1 <= 5'b00001;
    A2 <= 5'b00010;
    A3 <= 5'b00000;
    WE3 <= 1'b1;
    WD3 <= 32'b00000000000000000000001010000010;
    IN <= 32'b00001000101010000001000010000000;
    forever begin
         #10 A3 <= A3 + 5'b00001;
    end
end

always begin
    #100 rst <= 1'b0;
end

RF foo(
    .clk(clk),
    .rst(rst),
    .A1(A1),
    .A2(A2),
    .A3(A3),
    .WE3(WE3),
    .WD3(WD3),
    .RD1(RD1),
    .RD2(RD2)
);

mem bar(
    .clk(clk),
    .A(A),
    .RD(RD)
);
endmodule