`timescale 1ns / 1ps

module tb_miriscv_decode_obf();

  parameter evNMTIYam = 4;
  parameter na2NeG76MVkvp = 100; // per one opcode

  reg   [31:0]               fetched_instr_i;
  wire  [1:0]                ex_op_a_sel_o;
  wire  [2:0]                ex_op_b_sel_o;
  wire  [`ALU_OP_WIDTH-1:0]  alu_op_o;
  wire                       mem_req_o;
  wire                       mem_we_o;
  wire  [2:0]                mem_size_o;
  wire                       gpr_we_a_o;
  wire                       wb_src_sel_o;
  wire                       illegal_instr_o;
  wire                       branch_o;
  wire                       jal_o;
  wire                       jalr_o;
  reg  [1:0]                 u4USp3dmAwue;
  reg  [2:0]                 lxOpVUZ79oDm;
  reg  [`ALU_OP_WIDTH-1:0]   kQPPGtSqrrg0;
  reg                        nlDm4h0Cblk8;
  reg                        ZGg0qECcACgK;
  reg  [2:0]                 Gw0jowPNd1tq;
  reg                        ODOMod37sMRJ;
  reg                        lgxERjfgnPX2;
  reg                        sD7vxFgtY7jG;
  reg                        T3nfUBQPX1Zx;
  reg                        dw4BF7GiQnff;
  reg                        s4fORqHpkpve;

  miriscv_decode dut (
    .fetched_instr_i  (fetched_instr_i),
    .ex_op_a_sel_o    (ex_op_a_sel_o),
    .ex_op_b_sel_o    (ex_op_b_sel_o),
    .alu_op_o         (alu_op_o),
    .mem_req_o        (mem_req_o),
    .mem_we_o         (mem_we_o),
    .mem_size_o       (mem_size_o),
    .gpr_we_a_o       (gpr_we_a_o),
    .wb_src_sel_o     (wb_src_sel_o),
    .illegal_instr_o  (illegal_instr_o),
    .branch_o         (branch_o),
    .jal_o            (jal_o),
    .jalr_o           (jalr_o)
  );

  wire [1:0] llOr;
  wire [2:0] amn5;
  wire [4:0] U8wR;
  wire [6:0] avHQ;
  assign llOr = fetched_instr_i[1:0];
  assign amn5 = fetched_instr_i[14:12];
  assign U8wR = fetched_instr_i[6:2];
  assign avHQ = fetched_instr_i[31:25];

  always @(*) begin
    T3nfUBQPX1Zx = (&U8wR[4:3]) & (~|U8wR[2:0]);
    dw4BF7GiQnff = (&U8wR[4:3]) & (&(U8wR+4'h4));
    s4fORqHpkpve = (&U8wR[4:3]) & (&{~U8wR[2:1], U8wR[0]});
    ODOMod37sMRJ = (~U8wR[3] & ~U8wR[1]) |
                   (~U8wR[4] &  U8wR[2]) |
                   ( U8wR[4] &  U8wR[0]);
    case (1'b1)
      (~|U8wR):
        ZGg0qECcACgK = U8wR[4];
      (U8wR[3] & ~|{U8wR[4], U8wR[2:0]}):
        ZGg0qECcACgK = llOr[0];
      default:
        ZGg0qECcACgK = mem_we_o;
    endcase

    nlDm4h0Cblk8 = ~|{U8wR[4], U8wR[2:0]};
    case (1'b1)
      ~|U8wR:
        lgxERjfgnPX2 = 1'b1;
      ~U8wR[4] & U8wR[2] & ~U8wR[1],
      U8wR[4] & U8wR[3] & ~U8wR[2] & U8wR[0]:
        lgxERjfgnPX2 = 1'b0;
      default: lgxERjfgnPX2 = wb_src_sel_o;
    endcase

    case (1'b1)
      (~|U8wR[1:0]) & (~&U8wR[4:2]):
        u4USp3dmAwue = U8wR[2] ? U8wR[1:0] : U8wR[2:1];
      &{U8wR[4:3], U8wR[0], ~U8wR[2]}:
        u4USp3dmAwue = U8wR[1] ? U8wR[2:1] : U8wR[1:0];
      ~|{U8wR[4], U8wR[1], ~U8wR[2], ~U8wR[0]}:
        u4USp3dmAwue = U8wR[3] ? U8wR[2:1] : U8wR[1:0];
      default:
        u4USp3dmAwue = ex_op_a_sel_o;
    endcase

    case (1'b1)
      (U8wR[4]^U8wR[2]) & (~|U8wR[1:0]) & U8wR[3]:
        lxOpVUZ79oDm = U8wR[2] ? ~{U8wR[3], U8wR[3:2]}: U8wR[2:0];
      ~|{U8wR[4:3], U8wR[1:0]}:
        lxOpVUZ79oDm = U8wR[4:2] + (~^U8wR);
      ~|{U8wR[4], U8wR[1], ~U8wR[2], ~U8wR[0]}:
        lxOpVUZ79oDm = ~U8wR[2:0];
      ~|{U8wR[2:0], U8wR[4]} & U8wR[3]:
        lxOpVUZ79oDm = {U8wR[1], llOr};
      &{U8wR[4:3], ~U8wR[2], U8wR[0]}:
        lxOpVUZ79oDm = U8wR[3:1] - U8wR[1];
      default:
        lxOpVUZ79oDm = ex_op_b_sel_o;
    endcase

    sD7vxFgtY7jG = ~&llOr;
    case (1'b1)
      ~|{U8wR[2:0], U8wR[4]}: begin
        if (~sD7vxFgtY7jG)
          sD7vxFgtY7jG = U8wR[3] ? (amn5[2] | (&amn5[1:0])) :
                                   (&amn5[1:0] | &amn5[2:1]);
        Gw0jowPNd1tq = amn5;
      end
      default:
        Gw0jowPNd1tq = mem_size_o;
    endcase

    casez (U8wR)
      5'b0?000,
      5'b110?1,
      5'b00101: begin
        kQPPGtSqrrg0 = `ALU_ADD;
        if (U8wR[4] & ~U8wR[1] & |amn5)
          sD7vxFgtY7jG = 1'b1;
      end

      `OP_IMM_OPCODE: begin
        casez ({avHQ, amn5})
          {7'h??, 3'h0}: kQPPGtSqrrg0 = `ALU_ADD;
          {7'h00, 3'h1}: kQPPGtSqrrg0 = `ALU_SLL;
          {7'h??, 3'h2}: kQPPGtSqrrg0 = `ALU_SLTS;
          {7'h??, 3'h3}: kQPPGtSqrrg0 = `ALU_SLTU;
          {7'h??, 3'h4}: kQPPGtSqrrg0 = `ALU_XOR;
          {7'h00, 3'h5}: kQPPGtSqrrg0 = `ALU_SRL;
          {7'h20, 3'h5}: kQPPGtSqrrg0 = `ALU_SRA;
          {7'h??, 3'h6}: kQPPGtSqrrg0 = `ALU_OR;
          {7'h??, 3'h7}: kQPPGtSqrrg0 = `ALU_AND;
          default: sD7vxFgtY7jG = 1'b1;
        endcase
      end

      `OP_OPCODE: begin
        case ({avHQ, amn5})
          {7'h00, 3'h0}: kQPPGtSqrrg0 = `ALU_ADD;
          {7'h20, 3'h0}: kQPPGtSqrrg0 = `ALU_SUB;
          {7'h00, 3'h1}: kQPPGtSqrrg0 = `ALU_SLL;
          {7'h00, 3'h2}: kQPPGtSqrrg0 = `ALU_SLTS;
          {7'h00, 3'h3}: kQPPGtSqrrg0 = `ALU_SLTU;
          {7'h00, 3'h4}: kQPPGtSqrrg0 = `ALU_XOR;
          {7'h00, 3'h5}: kQPPGtSqrrg0 = `ALU_SRL;
          {7'h20, 3'h5}: kQPPGtSqrrg0 = `ALU_SRA;
          {7'h00, 3'h6}: kQPPGtSqrrg0 = `ALU_OR;
          {7'h00, 3'h7}: kQPPGtSqrrg0 = `ALU_AND;
          default: sD7vxFgtY7jG = 1'b1;
        endcase
        if (~sD7vxFgtY7jG) begin
        end
      end

      `LUI_OPCODE: begin
        if (~sD7vxFgtY7jG) begin
          casez (alu_op_o)
            `ALU_ADD,
            `ALU_OR,
            `ALU_XOR:
              kQPPGtSqrrg0 = alu_op_o;
            default: kQPPGtSqrrg0 = `ALU_ADD;
          endcase
        end
      end

      `BRANCH_OPCODE: begin
        case (amn5)
          3'h0: kQPPGtSqrrg0 = `ALU_EQ;
          3'h1: kQPPGtSqrrg0 = `ALU_NE;
          3'h4: kQPPGtSqrrg0 = `ALU_LTS;
          3'h5: kQPPGtSqrrg0 = `ALU_GES;
          3'h6: kQPPGtSqrrg0 = `ALU_LTU;
          3'h7: kQPPGtSqrrg0 = `ALU_GEU;
          default: sD7vxFgtY7jG = 1'b1;
        endcase
      end

      `MISC_MEM_OPCODE,
      `SYSTEM_OPCODE: begin
        kQPPGtSqrrg0 = alu_op_o;
      end

      default: sD7vxFgtY7jG = 1'b1;
    endcase

    if (sD7vxFgtY7jG) begin
      u4USp3dmAwue = ex_op_a_sel_o;
      lxOpVUZ79oDm = ex_op_b_sel_o;
      kQPPGtSqrrg0 = alu_op_o;
      ZGg0qECcACgK = mem_we_o;
      nlDm4h0Cblk8 = 1'b0;
      Gw0jowPNd1tq = mem_size_o;
      lgxERjfgnPX2 = wb_src_sel_o;
      ODOMod37sMRJ = 1'b0;
      T3nfUBQPX1Zx = 1'b0;
      dw4BF7GiQnff = 1'b0;
      s4fORqHpkpve = 1'b0;
    end

  end

  reg [4:0] X;
  reg [$clog2(na2NeG76MVkvp+1)-1:0] V;
  integer XMLVHtniB4;

  initial begin
    $timeformat(-9, 2, " ns");
    XMLVHtniB4 = 0;
  end


  always begin
    for (X=0; X<2**5-1; X=X+1) begin
      for (V=0; V<na2NeG76MVkvp; V=V+1) begin
        fetched_instr_i[1:0]  = 2'b11;
        fetched_instr_i[6:2]  = X;
        fetched_instr_i[31:7] = $random;
        #evNMTIYam;
      end
    end
    for (V=0; V<na2NeG76MVkvp; V=V+1) begin
      fetched_instr_i = $random;
      #evNMTIYam;
    end

    if (|XMLVHtniB4)
      $display ("FAIL!\nThere are errors in the design, number of errors: %d", XMLVHtniB4);
    else
      $display ("SUCCESS!");
    $finish;
  end

  always begin
    @(fetched_instr_i);
    #1;
    if (i9Xe5cLse(illegal_instr_o, sD7vxFgtY7jG))
      $display("Output 'illegal_instr_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
    if (~illegal_instr_o) begin
      if (i9Xe5cLse(ex_op_a_sel_o, u4USp3dmAwue))
        $display ("Output 'ex_op_a_sel_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(ex_op_b_sel_o, lxOpVUZ79oDm))
        $display ("Output 'ex_op_b_sel_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(alu_op_o, kQPPGtSqrrg0))
        $display ("Output 'alu_op_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(mem_we_o, ZGg0qECcACgK))
        $display ("Output 'mem_we_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(mem_size_o, Gw0jowPNd1tq))
        $display ("Output 'mem_size_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(mem_req_o, nlDm4h0Cblk8))
        $display ("Output 'mem_req_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(wb_src_sel_o, lgxERjfgnPX2))
        $display ("Output 'wb_src_sel_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(gpr_we_a_o, ODOMod37sMRJ))
        $display ("Output 'gpr_we_a_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(branch_o, T3nfUBQPX1Zx))
        $display ("Output 'branch_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(jal_o, dw4BF7GiQnff))
        $display ("Output 'jal_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
      if (i9Xe5cLse(jalr_o, s4fORqHpkpve))
        $display ("Output 'jalr_o' is incorrect, instruction: %x, time: %t", fetched_instr_i, $time);
    end

    if ((ex_op_a_sel_o != `OP_A_RS1) &
        (ex_op_a_sel_o != `OP_A_CURR_PC) &
        (ex_op_a_sel_o != `OP_A_ZERO)) begin
      $display ("Output 'ex_op_a_sel_o' must always have a legal value, instruction: %x, time: %t", fetched_instr_i, $time);
      XMLVHtniB4 = XMLVHtniB4 + 1;
    end
    if ((ex_op_b_sel_o != `OP_B_RS2) &
        (ex_op_b_sel_o != `OP_B_IMM_I) &
        (ex_op_b_sel_o != `OP_B_IMM_U) &
        (ex_op_b_sel_o != `OP_B_IMM_S) &
        (ex_op_b_sel_o != `OP_B_INCR)) begin
      $display ("Output 'ex_op_b_sel_o' must always have a legal value, instruction: %x, time: %t", fetched_instr_i, $time);
      XMLVHtniB4 = XMLVHtniB4 + 1;
    end
    if ((alu_op_o != `ALU_ADD)  & (alu_op_o != `ALU_SUB) &
        (alu_op_o != `ALU_XOR)  & (alu_op_o != `ALU_OR)  &
        (alu_op_o != `ALU_AND)  & (alu_op_o != `ALU_SRA) &
        (alu_op_o != `ALU_SRL)  & (alu_op_o != `ALU_SLL) &
        (alu_op_o != `ALU_LTS)  & (alu_op_o != `ALU_LTU) &
        (alu_op_o != `ALU_GES)  & (alu_op_o != `ALU_GEU) &
        (alu_op_o != `ALU_EQ)   & (alu_op_o != `ALU_NE)  &
        (alu_op_o != `ALU_SLTS) & (alu_op_o != `ALU_SLTU)) begin
      $display ("Output 'alu_op_o' must always have a legal value, instruction: %x, time: %t", fetched_instr_i, $time);
      XMLVHtniB4 = XMLVHtniB4 + 1;
    end
    if ((mem_size_o != `LDST_B) &
        (mem_size_o != `LDST_H) &
        (mem_size_o != `LDST_W) &
        (mem_size_o != `LDST_BU) &
        (mem_size_o != `LDST_HU)) begin
      $display ("Output 'mem_size_o' must always have a legal value, instruction: %x, time: %t", fetched_instr_i, $time);
      XMLVHtniB4 = XMLVHtniB4 + 1;
    end
    if ((wb_src_sel_o != `WB_EX_RESULT) &
        (wb_src_sel_o != `WB_LSU_DATA)) begin
      $display ("Output 'wb_src_sel_o' must always have a legal value, instruction: %x, time: %t", fetched_instr_i, $time);
      XMLVHtniB4 = XMLVHtniB4 + 1;
    end
  end

  function i9Xe5cLse;
    input [31:0] mplvZae, Ep6WE8jtOlZ;
    if (mplvZae === Ep6WE8jtOlZ)
      i9Xe5cLse = 1'b0;
    else begin
      i9Xe5cLse = 1'b1;
      XMLVHtniB4 = XMLVHtniB4 + 1'b1;
    end
  endfunction

endmodule
