`include "miriscv_defines.v"

`define ON 1'b1
`define OFF 1'b0

module miriscv_decode(
    input   [31:0]  fetched_instr_i,
    output  reg [1:0]  ex_op_a_sel_o,
    output  reg [2:0]  ex_op_b_sel_o,
    output  reg [`ALU_OP_WIDTH - 1:0] alu_op_o,
    output  reg mem_req_o,
    output  reg mem_we_o,
    output  reg [2:0]   mem_size_o,
    output  reg gpr_we_a_o,
    output  reg wb_src_sel_o,
    output  reg illegal_instr_o,
    output  reg branch_o,
    output  reg jal_o,
    output  reg jalr_o
);
    wire    [1:0]  no_legal_opcode = fetched_instr_i[1:0];

    wire    [4:0]  opcode = fetched_instr_i[6:2];
    wire    [6:0]    func7 = fetched_instr_i[31:25];
    wire    [2:0]    func3 = fetched_instr_i[14:12];

    always@(*)
    begin
    case(no_legal_opcode)
    2'b11:begin
            case(opcode)

            `LOAD_OPCODE:   begin       //(I-type) �������� ���������� �� Data Memory
                wb_src_sel_o = `WB_LSU_DATA;    //������ ���������� �� ������
                ex_op_a_sel_o = `OP_A_RS1;  //�������� ��� ��� (�������)
                ex_op_b_sel_o = `OP_B_IMM_I;  //(���������)
                alu_op_o = `ALU_ADD;    // rs1 + imm
                mem_we_o = `OFF;        //������ �� ������
                gpr_we_a_o = `ON;      //���� �� ������ � ����������� ����

                illegal_instr_o = `OFF;
                mem_req_o = `ON;
                branch_o = `OFF;
                jal_o = `OFF;
                jalr_o = `OFF;

                case(func3)             //�������� ������ ����� ����� �� ����� �������
                    3'h0:mem_size_o = `LDST_B ; 
                    3'h1: mem_size_o = `LDST_H ; 
                    3'h2: mem_size_o = `LDST_W ; 
                    3'h4: mem_size_o = `LDST_BU ;
                    3'h5: mem_size_o = `LDST_HU; 
                    default: begin 
                        illegal_instr_o = `ON;
                        jalr_o = `OFF;
                        jal_o = `OFF;
                        branch_o = `OFF;
                        gpr_we_a_o = `OFF;
                        mem_req_o = `OFF;
                    end
                endcase
            end

            `MISC_MEM_OPCODE:   begin 
                illegal_instr_o = `OFF;
                jalr_o = `OFF;
                jal_o = `OFF;
                branch_o = `OFF;
                gpr_we_a_o = `OFF;
                mem_req_o = `OFF;
            end

            `OP_IMM_OPCODE:   begin     //(I-type) ���������� �� ��� ��� ��������� �� �������� � ����������
                illegal_instr_o = `OFF;

                ex_op_a_sel_o = `OP_A_RS1;  //�������� ��� ��� (�������)
                ex_op_b_sel_o = `OP_B_IMM_I;  //(���������)
                gpr_we_a_o = `ON;      //���� �� ������ � �������
                wb_src_sel_o = `WB_EX_RESULT;    //������ ���������� �� ���

                branch_o = `OFF;
                jal_o = `OFF;
                jalr_o = `OFF;
                mem_req_o = `OFF;
                mem_size_o = `OFF;
                mem_we_o = `OFF;

                casez ({func7, func3})  //�������� ����������� �� ��� ��������
                    {7'h??, 3'h0}: alu_op_o = `ALU_ADD;
                    {7'h00, 3'h1}: alu_op_o = `ALU_SLL;     
                    {7'h??, 3'h2}: alu_op_o = `ALU_SLTS;
                    {7'h??, 3'h3}: alu_op_o = `ALU_SLTU;
                    {7'h??, 3'h4}: alu_op_o = `ALU_XOR; 
                    {7'h00, 3'h5}: alu_op_o = `ALU_SRL; 
                    {7'h20, 3'h5}: alu_op_o = `ALU_SRA; 
                    {7'h??, 3'h6}: alu_op_o = `ALU_OR;
                    {7'h??, 3'h7}: alu_op_o = `ALU_AND; 
                    default: begin 
                        illegal_instr_o = `ON;
                        jalr_o = `OFF;
                        jal_o = `OFF;
                        branch_o = `OFF;
                        gpr_we_a_o = `OFF;
                        mem_req_o = `OFF;
                    end   
                endcase
            end

            `AUIPC_OPCODE:   begin      //(U-type) �������� ������� �������� 
                illegal_instr_o = `OFF;
                ex_op_a_sel_o = `OP_A_CURR_PC;
                ex_op_b_sel_o = `OP_B_IMM_U;
                alu_op_o = `ALU_ADD;
                wb_src_sel_o = `WB_EX_RESULT; 
                gpr_we_a_o = `ON;

                branch_o = `OFF;
                jal_o = `OFF;
                jalr_o = `OFF;
                mem_req_o = `OFF;
                mem_size_o = `OFF;
                mem_we_o = `OFF;
            end

            `STORE_OPCODE:   begin      //(S-Type) ������ � Data Memory �� Registers File
                illegal_instr_o = `OFF;
                mem_we_o = `ON;         // ����� � ������
                ex_op_b_sel_o = `OP_B_IMM_S;    //�� ������ ���� ��� ���������, ��������� �� 2� ������
                ex_op_a_sel_o = `OP_A_RS1;      //������ ������� �� ������������ �����
                alu_op_o = `ALU_ADD;            //���������� �� ���
                gpr_we_a_o = `OFF;              //� RF ������ �� �����
                wb_src_sel_o = `WB_EX_RESULT;

                branch_o = `OFF;
                jal_o = `OFF;
                jalr_o = `OFF;
                mem_req_o = `ON;

                case(func3)
                    3'h0: mem_size_o = `LDST_B;
                    3'h1: mem_size_o = `LDST_H;
                    3'h2: mem_size_o = `LDST_W;
                    default: begin 
                        illegal_instr_o = `ON;
                        jalr_o = `OFF;
                        jal_o = `OFF;
                        branch_o = `OFF;
                        gpr_we_a_o = `OFF;
                        mem_req_o = `OFF;
                    end
                endcase
            end

            `OP_OPCODE:   begin          //(R-type) ���������� �� ��� ��� ����� ����������
                illegal_instr_o = `OFF;
                
                ex_op_a_sel_o = `OP_A_RS1;      //(�������)
                ex_op_b_sel_o = `OP_B_RS2;      //(�������)
                gpr_we_a_o = `ON;               //���� �� ������ � �������
                wb_src_sel_o = `WB_EX_RESULT;    //������ ���������� �� ���

                branch_o = `OFF;
                jal_o = `OFF;
                jalr_o = `OFF;
                mem_req_o = `OFF;
                mem_size_o = `OFF;
                mem_we_o = `OFF;

                case({func7, func3})        //����� �������� �� ���
                    {7'h00, 3'h0}: alu_op_o = `ALU_ADD;
                    {7'h20, 3'h0}: alu_op_o = `ALU_SUB;
                    {7'h00, 3'h1}: alu_op_o = `ALU_SLL;
                    {7'h00, 3'h2}: alu_op_o = `ALU_SLTS;
                    {7'h00, 3'h3}: alu_op_o = `ALU_SLTU;
                    {7'h00, 3'h4}: alu_op_o = `ALU_XOR;
                    {7'h00, 3'h5}: alu_op_o = `ALU_SRL;
                    {7'h20, 3'h5}: alu_op_o = `ALU_SRA;
                    {7'h00, 3'h6}: alu_op_o = `ALU_OR;
                    {7'h00, 3'h7}: alu_op_o = `ALU_AND;
                    default: begin 
                        illegal_instr_o = `ON;
                        jalr_o = `OFF;
                        jal_o = `OFF;
                        branch_o = `OFF;
                        gpr_we_a_o = `OFF;
                        mem_req_o = `OFF;
                        end
                endcase
            end

            `LUI_OPCODE:   begin         //(U-type) �������� ������� ��������
                illegal_instr_o = `OFF;
                ex_op_a_sel_o = `OP_A_ZERO;      //(����������� 0)
                ex_op_b_sel_o = `OP_B_IMM_U;      //(������� ��������� �� ����������)
                gpr_we_a_o = `ON;          //���� �� ������ � �������
                alu_op_o = `ALU_ADD;        //0 + upper_imm
                wb_src_sel_o = `WB_EX_RESULT;    //������ ���������� �� ���

                branch_o = `OFF;
                jal_o = `OFF;
                jalr_o = `OFF;
                mem_req_o = `OFF;
                mem_we_o = `OFF;
            end

            `BRANCH_OPCODE:   begin     //(B-type)  ���������� ��������� ��������
                illegal_instr_o = `OFF;
                branch_o = `ON;                  //�� ������������� ��������� ��������, ������ ���������� "if"
                ex_op_a_sel_o = `OP_A_RS1;      //(�������)
                ex_op_b_sel_o = `OP_B_RS2;      //(�������)
                gpr_we_a_o = `OFF;              //������ ������ �� �����
                mem_we_o = `OFF;

                jal_o = `OFF;
                jalr_o = `OFF;


                case(func3)
                        3'h0: alu_op_o = `ALU_EQ;
                        3'h1: alu_op_o = `ALU_NE;
                        3'h4: alu_op_o = `ALU_LTS;
                        3'h5: alu_op_o = `ALU_GES;
                        3'h6: alu_op_o = `ALU_LTU;
                        3'h7: alu_op_o = `ALU_GEU;
                    default: begin 
                        illegal_instr_o = `ON;
                        jalr_o = `OFF;
                        jal_o = `OFF;
                        branch_o = `OFF;
                        gpr_we_a_o = `OFF;
                        mem_req_o = `OFF;
                        end
                endcase
            end

            `JALR_OPCODE:   begin       //(I-type)  ���������� ������������ �������� � ���������
                case(func3)
                3'b000:begin
                    illegal_instr_o = `OFF;
                    jalr_o = `ON;
                    ex_op_a_sel_o = `OP_A_CURR_PC;
                    ex_op_b_sel_o = `OP_B_INCR;
                    alu_op_o = `ALU_ADD;
                    gpr_we_a_o = `ON;

                    branch_o = `OFF;
                    jal_o = `OFF;
                    end
                default: begin 
                    illegal_instr_o = `ON;
                    jalr_o = `OFF;
                    jal_o = `OFF;
                    branch_o = `OFF;
                    gpr_we_a_o = `OFF;
                    mem_req_o = `OFF;
                    end
                endcase
            end

            `JAL_OPCODE:   begin        //(J-type) ���������� ������������ ��������
                illegal_instr_o = `OFF;
                ex_op_a_sel_o = `OP_A_CURR_PC;
                ex_op_b_sel_o = `OP_B_INCR;
                jal_o = `ON;
                alu_op_o = `ALU_ADD;
                wb_src_sel_o = `WB_EX_RESULT; 
                gpr_we_a_o = `ON; 
                branch_o = `OFF;
                alu_op_o = `ALU_ADD;

                jalr_o = `OFF;
            end

            `SYSTEM_OPCODE:   begin 
                illegal_instr_o = `OFF;
                jalr_o = `OFF;
                jal_o = `OFF;
                branch_o = `OFF;
                gpr_we_a_o = `OFF;
                mem_req_o = `OFF;
            end

            default: begin 
                illegal_instr_o = `ON;
                jalr_o = `OFF;
                jal_o = `OFF;
                branch_o = `OFF;
                gpr_we_a_o = `OFF;
                mem_req_o = `OFF;
                end
            endcase
        end
        default: begin 
            illegal_instr_o = `ON;
            jalr_o = `OFF;
            jal_o = `OFF;
            branch_o = `OFF;
            gpr_we_a_o = `OFF;
            mem_req_o = `OFF;
            end
    endcase
    end
endmodule