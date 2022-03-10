//`timescale 1ns / 1ps

//module arch(
//    input clk,
//    input rst,
//    input [31:0] IN,
//    output [31:0] OUT
//    );
//wire [31:0] instr;   

//mem mem_connection(
//    .clk (clk),
//    .A(PC),
//    .RD(instr)
//);

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
//wire WE; assign WE = instr[29]|instr[28];
//wire [1:0] WS; assign WS = instr[29:28];
//wire [4:0] ALUop; assign ALUop = instr[27:23];
//wire [4:0] RA1; assign RA1 = instr[22:18];
//wire [4:0] RA2; assign RA2 = instr[17:13];
//wire [7:0] const; assign const = instr[12:5];
//wire [4:0] WA; assign WA = instr[4:0];


//reg [31:0] WD=0;
//wire [31:0] Result; 

//wire [31:0] RD2;
//wire [31:0] RD1;
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
//RF RF_connection(
//    .clk(clk),
//    .A1(RA1),
//    .A2(RA2),
//    .A3(WA),
//    .RD1(RD1),
//    .RD2(RD2),
//    .WD3(WD),
//    .WE3(WE),
//    .rst (rst)
//);

//ALU ALU_connection(
//    .ALUop(ALUop),
//    .A(RD1),
//    .B(RD2),
//    .Result(Result),
//    .Flag(Flag)
//);
//endmodule
//`timescale 1ns / 1ps

//module arch(
//    input clk, reset,
//    output flag
//    );
    
//wire [31:0] instr; 	              //инструкция 
//wire [1:0] ex_op_a_sel_o; 		  //Управляющий сигнал мультиплексора для выбора первого операнда АЛУ
//wire [2:0] ex_op_b_sel_o; 		  //Управляющий сигнал мультиплексора для выбора второго операнда АЛУ
//wire [5:0] alu_op_o; 			  //Операция АЛУ
//wire mem_req_o; 				  //Запрос на доступ к памяти (часть интерфейса памяти)
//wire mem_we_o; 					  //Сигнал разрешения записи в память, «write enable» (при равенстве нулю происходит чтение)
//wire [2:0] mem_size_o; 		      //Управляющий сигнал для выбора размера слова при чтении-записи в память(часть интерфейса памяти)
//wire gpr_we_a_o; 				  //Сигнал разрешения записи в регистровый файл
//wire wb_src_sel_o; 			      //Управляющий сигнал мультиплексора для выбора данных, записываемых в регистровый файл
//wire illegal_instr_o;             //Сигнал о некорректной инструкции
//wire branch_o; 					  //Сигнал об инструкции условного перехода
//wire jal_o; 					  //Сигнал об инструкции безусловного перехода jal
//wire jalr_o; 					  //Сигнал об инструкции безусловного перехода jarl
    
    
//reg  [31:0]  pc_adr;
//wire [31:0]  rd_1, rd_2, dm_rd;
//reg  [31:0]  wd_3;
//reg  [31:0]	 alu_operand_a, alu_operand_b;
//wire [31:0]  result;
//wire comp;
//wire [31:0]  imm_i, imm_s, imm_j, imm_b;

//assign imm_i = {{20{instr[31]}}, instr[31:20]};//for negative numbers.
//assign imm_s = {{21{instr[31]}}, instr[31:25], instr[11:7]};
//assign imm_j = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
//assign imm_b = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};

//reg  [31:0]  jmp_const;

//miriscv_decode Main_Decoder(
//	.fetched_instr_i(instr),
//	.ex_op_a_sel_o(ex_op_a_sel_o), 
//	.ex_op_b_sel_o(ex_op_b_sel_o),
//	.alu_op_o(alu_op_o),
//	.mem_req_o(mem_req_o),
//	.mem_we_o(mem_we_o),
//	.mem_size_o(mem_size_o),
//	.gpr_we_a_o(gpr_we_a_o),
//	.wb_src_sel_o(wb_src_sel_o),
//	.illegal_instr_o(illegal_instr_o),
//	.branch_o(branch_o),
//	.jal_o(jal_o),
//	.jalr_o(jalr_o)
//);

//miriscv_lsu lsu(
//	.clk_i(clk),
//	.arstn_i(reset),
		
//	.data_received_i(data_received_i),																						
//	.data_rdata_i(data_rdata_i),		
//	.data_req_o(data_req_o),			
//	.data_we_o(data_we_o),		
// 	.data_be_o(data_be_o), 			
//	.data_addr_o(data_addr_o),
//	.data_wdata_o(data_wdata_o),
  
//	.lsu_addr_i(result),			
//	.lsu_we_i(mem_we_o),			
//	.lsu_size_i(mem_size_o), 	
//	.lsu_data_i(rd_2),			
//	.lsu_req_i(mem_req_o),			
//	.lsu_stall_req_o(en_pc),	
//	.lsu_data_o(dm_rd)
//);

//mem Instruction_Memory(
//    .clk(clk),
//    .pc_adr(pc_adr), 
//    .rd(instr)
//);								


//RF RF_connection(
//	.clk(clk), 
//	.Reset(reset), 
//	.A1(instr[19:15]), 
//	.A2(instr[24:20]),
//	.A3(instr[11:7]), 
//	.WD3(wd_3), 
//	.WE3(gpr_we_a_o), 
//	.RD1(rd_1), 
//	.RD2(rd_2)
//);

////right from Register File to ALU
//always @(*) begin
//	case (ex_op_a_sel_o)
//		2'b00: alu_operand_a <= rd_1;
//		2'b01: alu_operand_a <= pc_adr; 
//		2'b10: alu_operand_a <= 0;
//	endcase
//end

//always @(*) begin
//	case (ex_op_b_sel_o)
//		3'b000: alu_operand_b <= rd_2;
//		3'b001: alu_operand_b <= imm_i; 
//		3'b010: alu_operand_b <= {instr[31:12], {12'b0}}; //warning?
//		3'b011: alu_operand_b <= imm_s;
//		3'b100: alu_operand_b <= 4;
//	endcase
//end
/////


//ALU ALU_connection(
//	.ALUop(alu_op_o), 
//	.A(alu_operand_a), 
//	.B(alu_operand_b), 
//	.Result(result), 
//	.Flag(comp)
//);

//data_memory Data_Memory(
//	.clk(clk),        
//	.A(result),    
//	.WD(rd_2),
//	.WE(mem_we_o),   					
//	.RD(dm_rd)
//);

////right from Data Memory 
//always @ (*) begin
//	case (wb_src_sel_o)
//		1'b0 : wd_3 = result;
//		1'b1 : wd_3 = dm_rd; 
//	endcase
//end
/////

//always @(*) begin
//	if (branch_o == 0) 
//		jmp_const = imm_j;
//	else
//		jmp_const = imm_b;
//end

//always @(posedge clk) begin
//	if (reset) 
//		pc_adr <= 0;
//	else begin
//		if (jalr_o)
//			pc_adr <= rd_1;
//		else
//			if (((comp & branch_o) | jal_o) == 0) 
//			    pc_adr <= pc_adr + 4;
//			else
//				pc_adr <= pc_adr + jmp_const;			
//	end
//end

//endmodule
`timescale 1ns / 1ps

module arch(
input clk, reset,
output flag,
    

input data_received_i,
input [31:0] data_rdata_i,
output data_req_o,
output data_we_o,
output [3:0] data_be_o,
output [31:0] data_addr_o,
output [31:0] data_wdata_o,
    
input	[31:0] instr_rdata_i,
output [31:0] instr_addr_o
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
wire en_pc;

assign imm_i = {{20{instr[31]}}, instr[31:20]};//for negative numbers.
assign imm_s = {{21{instr[31]}}, instr[31:25], instr[11:7]};
assign imm_j = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
assign imm_b = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};

reg  [31:0]  jmp_const;

wire enable_pc;
assign instr = instr_rdata_i;
assign instr_addr_o = pc_adr;	

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



miriscv_lsu lsu(
	.clk_i(clk),
	.arstn_i(reset),
		
	.data_received_i(data_received_i),																						
	.data_rdata_i(data_rdata_i),		
	.data_req_o(data_req_o),			
	.data_we_o(data_we_o),		
 	.data_be_o(data_be_o), 			
	.data_addr_o(data_addr_o),
	.data_wdata_o(data_wdata_o),
  
	.lsu_addr_i(result),			
	.lsu_we_i(mem_we_o),			
	.lsu_size_i(mem_size_o), 	
	.lsu_data_i(rd_2),			
	.lsu_req_i(mem_req_o),			
	.lsu_stall_req_o(en_pc),	
	.lsu_data_o(dm_rd)
);

RF regs_file(
	.clk(clk), 
	.Reset(reset), 
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


ALU alu(
	.ALUop(alu_op_o), 
	.A(alu_operand_a), 
	.B(alu_operand_b), 
	.Result(result), 
	.Flag(comp)
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
	if (reset) 
		pc_adr <= 0;
	else begin
	   if(!en_pc)
        if (jalr_o)
            pc_adr <= rd_1;
        else
            begin
                if (((comp & branch_o) | jal_o) == 0) 
                    pc_adr <= pc_adr + 4;
                else
                    pc_adr <= pc_adr + jmp_const;
                    
                //$display($time, "!my logs: \t pc=", pc_adr);
            end
	end
end

endmodule
