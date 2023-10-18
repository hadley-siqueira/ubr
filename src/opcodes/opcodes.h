#ifndef OPCODES_H
#define OPCODES_H

#define REG_V0 5

#define REG_A0 6
#define REG_A1 7
#define REG_A2 8
#define REG_A3 9
#define REG_A4 10
#define REG_A5 11
#define REG_A6 12
#define REG_A7 13
#define REG_T0 14
#define REG_T1 15
#define REG_T2 16
#define REG_T3 17
#define REG_T4 18
#define REG_T5 19
#define REG_T6 20
#define REG_T7 21

#define REG_SP 30

#define LINK_REGISTER 31

#define EIP 0
#define EBASE 1

enum TYPE_I_OPCODES {
    OPCODE_ADD = 0,
    OPCODE_SUB,
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_XOR,
    OPCODE_SLT,
    OPCODE_SLTU,
};

enum TYPE_II_OPCODES {
    OPCODE_LUI = 1,
    OPCODE_AUIPC,
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
    OPCODE_CSRR,
    OPCODE_CSRW,
};

#endif
