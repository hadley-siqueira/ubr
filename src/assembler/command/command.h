#ifndef COMMAND_H
#define COMMAND_H

#include "../binary_output/binary_output.h"

enum CommandKind {
    CMD_LABEL,

    CMD_BYTE_DIRECTIVE,
    CMD_INT_DIRECTIVE,
    CMD_ALIGN_DIRECTIVE,

    CMD_INST_ADD,
    CMD_INST_SUB,

    CMD_INST_AND,
    CMD_INST_OR,
    CMD_INST_XOR,

    CMD_INST_SLT,
    CMD_INST_SLTU,

    CMD_INST_BEQ,
    CMD_INST_BNE,
    CMD_INST_BLT,
    CMD_INST_BGE,
    CMD_INST_BLTU,
    CMD_INST_BGEU,

    CMD_INST_J,
    CMD_INST_JAL,
    CMD_INST_JALR,

    CMD_INST_LD,
    CMD_INST_LW,
    CMD_INST_LWU,
    CMD_INST_LH,
    CMD_INST_LHU,
    CMD_INST_LB,
    CMD_INST_LBU,

    CMD_INST_SD,
    CMD_INST_SW,
    CMD_INST_SH,
    CMD_INST_SB,

    CMD_INST_ADDI,
    CMD_INST_ANDI,
    CMD_INST_ORI,
    CMD_INST_XORI,
    CMD_INST_SLTI,
    CMD_INST_SLTIU,
    CMD_INST_LUI,
    CMD_INST_AUIPC,
    CMD_INST_LA,

    CMD_INST_ECALL,
    CMD_INST_ERET,

    // check later
    CMD_INST_CSRR,
    CMD_INST_CSRW,
};

class Command {
public:
    int get_kind();
    virtual void write_to(BinaryOutput* value);
    virtual int get_size();
    int get_offset();
    void set_offset(int offset);

protected:
    int kind;
    int offset;
};

#endif
