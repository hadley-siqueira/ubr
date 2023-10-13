#ifndef OPCODES_H
#define OPCODES_H

#define REG_V0 5
#define REG_A0 7

#define LINK_REGISTER 31

enum TYPE_I_OPCODES {
    OPCODE_ADD = 0,
    OPCODE_SUB,
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_XOR,
    OPCODE_SLT,
    OPCODE_SLTU,
};

enum TYPE_IV_OPCODES {
    OPCODE_ADDI = 0,
    OPCODE_ANDI,
    OPCODE_ORI,
    OPCODE_XORI,
    OPCODE_SLTI,
    OPCODE_SLTIU,
    OPCODE_LD,
    OPCODE_LW,
    OPCODE_LWU,
    OPCODE_LH,
    OPCODE_LHU,
    OPCODE_LB,
    OPCODE_LBU,
    OPCODE_SD,
    OPCODE_SW,
    OPCODE_SH,
    OPCODE_SB,
    OPCODE_BEQ,
    OPCODE_BNE,
    OPCODE_BLT,
    OPCODE_BLTU,
    OPCODE_BGE,
    OPCODE_BGEU,
    OPCODE_JALR,
    OPCODE_ECALL,
    OPCODE_ERET,
};

#endif
