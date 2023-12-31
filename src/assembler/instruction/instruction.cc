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
    case CMD_INST_ADD:
        write_binary_type_i(value, OPCODE_ADD);
        break;

    case CMD_INST_SUB:
        write_binary_type_i(value, OPCODE_SUB);
        break;

    case CMD_INST_AND:
        write_binary_type_i(value, OPCODE_AND);
        break;

    case CMD_INST_OR:
        write_binary_type_i(value, OPCODE_OR);
        break;

    case CMD_INST_XOR:
        write_binary_type_i(value, OPCODE_XOR);
        break;

    case CMD_INST_SLT:
        write_binary_type_i(value, OPCODE_SLT);
        break;

    case CMD_INST_SLTU:
        write_binary_type_i(value, OPCODE_SLTU);
        break;

    case CMD_INST_BEQ:
        write_binary_type_iv_i(value, OPCODE_BEQ);
        break;

    case CMD_INST_BNE:
        write_binary_type_iv_i(value, OPCODE_BNE);
        break;

    case CMD_INST_BLT:
        write_binary_type_iv_i(value, OPCODE_BLT);
        break;

    case CMD_INST_BGE:
        write_binary_type_iv_i(value, OPCODE_BGE);
        break;

    case CMD_INST_BLTU:
        write_binary_type_iv_i(value, OPCODE_BLTU);
        break;

    case CMD_INST_BGEU:
        write_binary_type_iv_i(value, OPCODE_BGEU);
        break;

    case CMD_INST_J:
        write_binary_type_iii(value, false);
        break;

    case CMD_INST_JAL:
        write_binary_type_iii(value, true);
        break;

    case CMD_INST_LD:
        write_binary_type_iv(value, OPCODE_LD);
        break;

    case CMD_INST_LW:
        write_binary_type_iv(value, OPCODE_LW);
        break;

    case CMD_INST_LWU:
        write_binary_type_iv(value, OPCODE_LWU);
        break;

    case CMD_INST_LH:
        write_binary_type_iv(value, OPCODE_LH);
        break;

    case CMD_INST_LHU:
        write_binary_type_iv(value, OPCODE_LHU);
        break;

    case CMD_INST_LB:
        write_binary_type_iv(value, OPCODE_LB);
        break;

    case CMD_INST_LBU:
        write_binary_type_iv(value, OPCODE_LBU);
        break;

    case CMD_INST_SD:
        write_binary_type_iv(value, OPCODE_SD);
        break;

    case CMD_INST_SW:
        write_binary_type_iv(value, OPCODE_SW);
        break;

    case CMD_INST_SH:
        write_binary_type_iv(value, OPCODE_SH);
        break;

    case CMD_INST_SB:
        write_binary_type_iv(value, OPCODE_SB);
        break;

    case CMD_INST_ADDI:
        write_binary_type_iv(value, OPCODE_ADDI);
        break;

    case CMD_INST_ANDI:
        write_binary_type_iv(value, OPCODE_ANDI);
        break;

    case CMD_INST_ORI:
        write_binary_type_iv(value, OPCODE_ORI);
        break;

    case CMD_INST_XORI:
        write_binary_type_iv(value, OPCODE_XORI);
        break;

    case CMD_INST_SLTI:
        write_binary_type_iv(value, OPCODE_SLTI);
        break;

    case CMD_INST_SLTIU:
        write_binary_type_iv(value, OPCODE_SLTIU);
        break;

    case CMD_INST_ECALL:
        write_binary_type_iv(value, OPCODE_ECALL);
        break;

    case CMD_INST_ERET:
        write_binary_type_iv(value, OPCODE_ERET);
        break;

    case CMD_INST_LUI:
        write_binary_type_ii(value, OPCODE_LUI);
        break;

    case CMD_INST_AUIPC:
        write_binary_type_ii(value, OPCODE_AUIPC);
        break;

    case CMD_INST_JALR:
        write_binary_type_iv_i(value, OPCODE_JALR);
        break;

    case CMD_INST_CSRR:
        write_binary_type_iv(value, OPCODE_CSRR);
        break;

    case CMD_INST_CSRW:
        write_binary_type_iv(value, OPCODE_CSRW);
        break;

    case CMD_INST_LA:
        write_load_address(value);
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

void Instruction::write_binary_type_iv(BinaryOutput* value, int opcode) {
    int inst = get_binary_type_iv(opcode);
    value->append32(inst);
}

void Instruction::write_binary_type_iii(BinaryOutput* value, bool link) {
    int inst = get_binary_type_iii(link);
    value->append32(inst);
}

void Instruction::write_binary_type_iv_i(BinaryOutput* value, int opcode) {
    int inst = get_binary_type_iv_i(opcode);
    value->append32(inst);
}

void Instruction::write_load_address(BinaryOutput* value) {
    int auipc = 0;
    int addi = 0;
    int rd = dest->to_int();
    int addr = 0;
    int addr20 = 0;
    int addr12 = 0;

    if (src1->get_kind() == VAL_NUMBER) {

    } else if (src1->get_kind() == VAL_ID) {
        addr = src1->to_int() - offset;
        addr20 = addr >> 12;
        addr12 = addr & 0xfff;
    }

    auipc = get_binary_type_ii(OPCODE_AUIPC, rd, addr20);
    addi = get_binary_type_iv(OPCODE_ADDI, rd, rd, addr12);
    value->append32(auipc);
    value->append32(addi);
}

int Instruction::get_binary_type_i(int func) {
    int inst = 4;

    inst = inst << 4 | (func >> 9) & 0xf;
    inst = inst << 5 | src1->to_int();
    inst = inst << 5 | src2->to_int();;
    inst = inst << 5 | dest->to_int();
    inst = inst << 10 | func & 0x3ff;

    return inst;
}

int Instruction::get_binary_type_ii(int opcode) {
    return get_binary_type_ii(opcode, dest->to_int(), src1->to_int());
}

int Instruction::get_binary_type_ii(int opcode, int rd, int immd) {
    int inst = 4;

    inst = inst << 4 | opcode & 0xf;
    inst = inst << 5 | rd;
    inst = inst << 20 | immd & 0xfffff;

    return inst;
}

int Instruction::get_binary_type_iii(bool link) {
    int inst = link ? 11 : 10;

    if (src1->get_kind() == VAL_NUMBER) {
        int addr = src1->to_int();
        addr = addr >> 1;
        inst = inst << 28 | addr & 0xfffffff;
    } else if (src1->get_kind() == VAL_ID) {
        int addr = src1->to_int() - offset;
        addr = addr >> 1;
        inst = inst << 28 | addr & 0xfffffff;
    }

    return inst;
}

int Instruction::get_binary_type_iv(int func) {
    int inst = 3;

    inst = inst << 5 | (func >> 3) & 0x1f;
    inst = inst << 5 | dest->to_int();
    inst = inst << 5 | src1->to_int();
    inst = inst << 3 | func & 7;
    inst = inst << 12 | src2->to_int() & 0xfff;

    return inst;
}

int Instruction::get_binary_type_iv(int func, int ra, int rb, int immd) {
    int inst = 3;

    inst = inst << 5 | (func >> 3) & 0x1f;
    inst = inst << 5 | ra;
    inst = inst << 5 | rb;
    inst = inst << 3 | func & 7;
    inst = inst << 12 | immd & 0xfff;

    return inst;
}

int Instruction::get_binary_type_iv_i(int func) {
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
    int size = 4;

    switch (kind) {
    case CMD_INST_LA:
        size = 8;
        break;
    }

    return size;
}
