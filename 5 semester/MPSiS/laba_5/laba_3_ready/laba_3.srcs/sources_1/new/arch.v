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
    output flag
    );
wire [31:0] instr; 	              //инструкция 
wire [1:0] ex_op_a_sel_o; 		  //Управляющий сигнал мультиплексора для выбора первого операнда АЛУ
wire [2:0] ex_op_b_sel_o; 		  //Управляющий сигнал мультиплексора для выбора второго операнда АЛУ
wire [5:0] alu_op_o; 			  //Операция АЛУ
wire mem_req_o; 				  //Запрос на доступ к памяти (часть интерфейса памяти)
wire mem_we_o; 					  //Сигнал разрешения записи в память, «write enable» (при равенстве нулю происходит чтение)
wire [2:0] mem_size_o; 		      //Управляющий сигнал для выбора размера слова при чтении-записи в память(часть интерфейса памяти)
wire gpr_we_a_o; 				  //Сигнал разрешения записи в регистровый файл
wire wb_src_sel_o; 			      //Управляющий сигнал мультиплексора для выбора данных, записываемых в регистровый файл
wire illegal_instr_o;             //Сигнал о некорректной инструкции
wire branch_o; 					  //Сигнал об инструкции условного перехода
wire jal_o; 					  //Сигнал об инструкции безусловного перехода jal
wire jalr_o; 					  //Сигнал об инструкции безусловного перехода jarl
    
    
reg  [31:0]  pc_adr;
wire [31:0]  rd_1, rd_2, dm_rd;
reg  [31:0]  wd_3;
reg  [31:0]	 alu_operand_a, alu_operand_b;
wire [31:0]  result;
wire comp;
wire [31:0]  imm_i, imm_s, imm_j, imm_b;

assign imm_i = {{20{instr[31]}}, instr[31:20]};//for negative numbers.
assign imm_s = {{21{instr[31]}}, instr[31:25], instr[11:7]};
assign imm_j = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
assign imm_b = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};

reg  [31:0]  jmp_const;

miriscv_decode Main_Decoder(
	.fetched_instr_i(instr),
	.ex_op_a_sel_o(ex_op_a_sel_o), 
	.ex_op_b_sel_o(ex_op_b_sel_o),
	.alu_op_o(alu_op_o),
	.mem_req_o(mem_req_o),
	.mem_we_o(mem_we_o),
	.mem_size_o(mem_size_o),
	.gpr_we_a_o(gpr_we_a_o),
	.wb_src_sel_o(wb_src_sel_o),
	.illegal_instr_o(illegal_instr_o),
	.branch_o(branch_o),
	.jal_o(jal_o),
	.jalr_o(jalr_o)
);

mem Instruction_Memory(
    .clk(clk),
	.pc_adr(pc_adr), 
	.rd(instr)
);	

//mem mem_connection(
//.clk (clk),
//.A(pc_adr[9:2]),
//.RD(instr)
//);

RF regs_file(
	.clk(clk), 
	.rst(rst), 
	.A1(instr[19:15]), 
	.A2(instr[24:20]),
	.A3(instr[11:7]), 
	.WD3(wd_3), 
	.WE3(gpr_we_a_o), 
	.RD1(rd_1), 
	.RD2(rd_2)
);
//right from Register File to ALU
always @(*) begin
	case (ex_op_a_sel_o)
		2'b00: alu_operand_a <= rd_1;
		2'b01: alu_operand_a <= pc_adr; 
		2'b10: alu_operand_a <= 0;
	endcase
end

always @(*) begin
	case (ex_op_b_sel_o)
		3'b000: alu_operand_b <= rd_2;
		3'b001: alu_operand_b <= imm_i; 
		3'b010: alu_operand_b <= {instr[31:12], {12'b0}}; //warning?
		3'b011: alu_operand_b <= imm_s;
		3'b100: alu_operand_b <= 4;
	endcase
end
///

//always @(posedge clk ) 
//begin
//    if (rst==1)
//    PC <=8'b0;
//    else begin
//         	case(B | (C && Flag))
//            	2'b00 : 
//            	       PC <= PC + 8'b00000001;
//            	2'b01 : 
    //            	       PC <= PC + const;
//         	endcase
//    	end
//end
    
//wire B; assign B = instr[31];
//wire C; assign C= instr[30];
//wire [1:0] WS; assign WS = instr[29:28];
//wire [4:0] ALUop; assign ALUop = instr[27:23];
//wire [7:0] const; assign const = instr[12:5];


//wire [31:0] Result; 

//wire Flag;
//reg [7:0] PC=0;
//assign OUT = RD1;

//always @(*) 
//begin
//    if (WE) begin
//                case(WS)
//                     2'b01: WD = IN;
//                     2'b10 : WD <= {{24{instr[12]}}, instr[12:5]};
//                     2'b11: WD = Result;
//                endcase
//            end
//end

ALU ALU_connection(
.ALUop(alu_op_o),
.A(alu_operand_a),
.B(alu_operand_b),
.Result(result),
.Flag(comp)
);

data_memory Data_Memory(
	.clk(clk),        
	.A(result),    
	.WD(rd_2),
	.WE(mem_we_o),   					
	.RD(dm_rd)
);

//right from Data Memory 
always @ (*) begin
	case (wb_src_sel_o)
		1'b0 : wd_3 = result;
		1'b1 : wd_3 = dm_rd; 
	endcase
end
///

always @(*) begin
	if (branch_o == 0) 
		jmp_const = imm_j;
	else
		jmp_const = imm_b;
end

always @(posedge clk) begin
	if (rst) 
		pc_adr <= 0;
	else begin
		if (jalr_o)
			pc_adr <= rd_1;
		else
			if (((comp & branch_o) | jal_o) == 0) 
			    pc_adr <= pc_adr + 4;
			else
				pc_adr <= pc_adr + jmp_const;			
	end
end
endmodule
