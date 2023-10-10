#include <iostream>
#include "instruction.h"

Instruction::Instruction(int kind) {
    this->kind = kind;
    dest = nullptr;
    src1 = nullptr;
    src2 = nullptr;
}

Instruction::~Instruction() {
    delete dest;
    delete src1;
    delete src2;
}

void Instruction::set_dest(Value* r) {
    dest = r;
}

void Instruction::set_src1(Value* r) {
    src1 = r;
}

void Instruction::set_src2(Value* r) {
    src2 = r;
}

void Instruction::write_to(BinaryOutput* value) {
    int inst = 0;

    switch (kind) {
    /*case CMD_INST_ADD:
        write_binary_type_i(value, F_ADD);
        break;

    case CMD_INST_SUB:
        write_binary_type_i(value, F_SUB);
        break;

    case CMD_INST_AND:
        write_binary_type_i(value, F_AND);
        break;

    case CMD_INST_OR:
        write_binary_type_i(value, F_OR);
        break;

    case CMD_INST_XOR:
        write_binary_type_i(value, F_XOR);
        break;*/

    case CMD_INST_BEQ:
        write_binary_type_iii(value, OPCODE_BEQ);
        break;

    case CMD_INST_LD:
        write_binary_type_ii(value, OPCODE_LD);
        break;

    case CMD_INST_LW:
        write_binary_type_ii(value, OPCODE_LW);
        break;

    case CMD_INST_LWU:
        write_binary_type_ii(value, OPCODE_LWU);
        break;

    case CMD_INST_LH:
        write_binary_type_ii(value, OPCODE_LH);
        break;

    case CMD_INST_LHU:
        write_binary_type_ii(value, OPCODE_LHU);
        break;

    case CMD_INST_LB:
        write_binary_type_ii(value, OPCODE_LB);
        break;

    case CMD_INST_LBU:
        write_binary_type_ii(value, OPCODE_LBU);
        break;

    case CMD_INST_SD:
        write_binary_type_ii(value, OPCODE_SD);
        break;

    case CMD_INST_SW:
        write_binary_type_ii(value, OPCODE_SW);
        break;

    case CMD_INST_SH:
        write_binary_type_ii(value, OPCODE_SH);
        break;

    case CMD_INST_SB:
        write_binary_type_ii(value, OPCODE_SB);
        break;

    case CMD_INST_ADDI:
        write_binary_type_ii(value, OPCODE_ADDI);
        break;
    }
}

void Instruction::write_binary_type_i(BinaryOutput* value, int func) {
    int inst = get_binary_type_i(func);
    value->append32(inst);
}

void Instruction::write_binary_type_ii(BinaryOutput* value, int opcode) {
    int inst = get_binary_type_ii(opcode);
    value->append32(inst);
}

void Instruction::write_binary_type_iii(BinaryOutput* value, int opcode) {
    int inst = get_binary_type_iii(opcode);
    value->append32(inst);
}

int Instruction::get_binary_type_i(int func) {
    int inst = 1;

    inst = inst << 7 | 0;
    inst = inst << 5 | src1->to_int();
    inst = inst << 5 | src2->to_int();;
    inst = inst << 5 | dest->to_int();
    inst = inst << 9 | func;

    return inst;
}

int Instruction::get_binary_type_ii(int func) {
    int inst = 3;

    inst = inst << 5 | (func >> 3) & 0x1f;
    inst = inst << 5 | dest->to_int();
    inst = inst << 5 | src1->to_int();
    inst = inst << 3 | func & 7;
    inst = inst << 12 | src2->to_int() & 0xfff;

    return inst;
}

int Instruction::get_binary_type_iii(int func) {
    int inst = 3;

    inst = inst << 5 | (func >> 3) & 0x1f;
    inst = inst << 5 | dest->to_int();
    inst = inst << 5 | src1->to_int();
    inst = inst << 3 | func & 7;

    if (src2->get_kind() == VAL_NUMBER) {
        int addr = src2->to_int();
        addr = addr >> 1;
        inst = inst << 12 | addr & 0xfff;
    } else if (src2->get_kind() == VAL_ID) {
        int addr = src2->to_int() - offset;
        addr = addr >> 1;
        inst = inst << 12 | addr & 0xfff;
    }

    return inst;
}

int Instruction::get_size() {
    return 4;
}
