`timescale 1ns / 1ps

module miriscv_lsu(
	input clk_i,
	input arstn_i,
	
	input data_received_i,						// есть ответ от памяти на входе data_rdata_i																			
	
	input [31:0] data_rdata_i,				    // запрошенные данные 
	output reg	data_req_o,					    // 1 - обратиться к памяти 
	output reg	data_we_o,					    // 1 - это запрос на запись, 0 - на чтение.
	output reg [3:0]	data_be_o,			    // к каким байтам слова идет обращение
	output reg [31:0] data_addr_o,		        // адрес, по которому идет обращение
	output reg [31:0] data_wdata_o,		        // данные, которые требуется записать
 
	input [31:0] lsu_addr_i,				// адрес, по которому хотим обратиться 
	input lsu_we_i,							// 1 - если нужно записать в память 
	input [2:0] lsu_size_i, 				//размер обрабатываемых данных (выбор разрядности mem_size_o)
	input [31:0] lsu_data_i,				// данные для записи в память 
	input lsu_req_i,						// 1 - обратиться к памяти 
	output reg lsu_stall_req_o,			    // используется как !enable pc 
	output reg [31:0] lsu_data_o			// данные для процессора
);

always @(*) begin
	lsu_stall_req_o = lsu_req_i && !data_received_i;
	data_req_o = lsu_stall_req_o;
	data_we_o = lsu_we_i;
	data_addr_o = lsu_addr_i;
	
	// query to memory
	if (lsu_req_i)
	begin
		if (lsu_we_i)
		begin
		//8-bit sig unsig
			if ((lsu_size_i == 3'd0) || (lsu_size_i == 3'd4))
			begin		
				case (lsu_addr_i[1:0])
					2'b00:
						data_be_o = 4'b0001;
					2'b01: 
						data_be_o = 4'b0010;
					2'b10:
						data_be_o = 4'b0100;
					2'b11: 
						data_be_o = 4'b1000;
				endcase
			
				data_wdata_o = {4{lsu_data_i[7:0]}};
			end
			//16-bit sig unsig
			if ((lsu_size_i == 3'd1) || (lsu_size_i == 3'd5))
			begin
				case (lsu_addr_i[1:0])
					2'b00:
						data_be_o = 4'b0011;
					2'b10:
						data_be_o = 4'b1100;
				endcase
				
                data_wdata_o = {2{lsu_data_i[15:0]}};
			end
			//32-bit
			if (lsu_size_i == 3'd2)
			 begin
				if (lsu_addr_i[1:0] == 2'b0)
				begin
    				data_wdata_o = lsu_data_i;
					data_be_o = 4'b1111;
				end
			end
		end
		else
		begin
			data_wdata_o = 0;
			data_be_o = 0;
			
			case (lsu_size_i)
				3'd0://8-bit num
					case (lsu_addr_i[1:0])
						2'b00:
							lsu_data_o = {{24{data_rdata_i[7]}}, data_rdata_i[7:0]};
						2'b01:
							lsu_data_o = {{24{data_rdata_i[15]}}, data_rdata_i[15:8]};
						2'b10:
							lsu_data_o = {{24{data_rdata_i[23]}}, data_rdata_i[23:16]};
						2'b11:
							lsu_data_o = {{24{data_rdata_i[31]}}, data_rdata_i[31:24]};
					endcase
						
				3'd1://16-bit num
					case (lsu_addr_i[1:0])
						2'b00:
							lsu_data_o = {{16{data_rdata_i[15]}}, data_rdata_i[15:0]};
						2'b10:
							lsu_data_o = {{16{data_rdata_i[31]}}, data_rdata_i[31:16]};
					endcase
					
				3'd2://32-bit num
					if (lsu_addr_i[1:0] == 2'b00)
						lsu_data_o = data_rdata_i;
					
				3'd4://8-bit num
					case (lsu_addr_i[1:0])
						2'b00:
							lsu_data_o = {24'b0, data_rdata_i[7:0]};
						2'b01: 
							lsu_data_o = {24'b0, data_rdata_i[15:8]};
						2'b10: 
							lsu_data_o = {24'b0, data_rdata_i[23:16]};
						2'b11: 
							lsu_data_o = {24'b0, data_rdata_i[31:24]};	
					endcase
						
				3'd5://16-bit num
					case (lsu_addr_i[1:0])
						2'b00: 
							lsu_data_o = {16'b0, data_rdata_i[15:0]};
						2'b10: 
							lsu_data_o = {16'b0, data_rdata_i[31:16]};
					endcase
			endcase
		end
	end
end


endmodule




