#include <fstream>
#include <sstream>
#include <iostream>

#include "emulator.h"
#include "../../opcodes/opcodes.h"

std::string hex64(uint64_t value) {
    std::stringstream out;

    for (int i = 60; i >= 0; i -= 4) {
        int k = (value >> i) & 0xf;

        if (k < 10) {
            out << (char) ('0' + k);
        } else {
            out << (char) ('a' + k - 10);
        }
    }

    return out.str();
}

Emulator::Emulator() {
    ip = 0;

    for (int i = 0; i < 32; ++i) {
        regs[i] = 0;
    }

    regs[30] = 2040;
    memory = new Memory();
}

Emulator::~Emulator() {
    delete memory;
}

void Emulator::read_binary(std::string path) {
    memory->read_binary(path);
}

void Emulator::tick() {
    fetch_instruction();
    decode_instruction();
    execute_instruction();
}

void Emulator::fetch_instruction() {
    instruction = memory->read_u32(ip);
}

void Emulator::decode_instruction() {
    inst_size = 4;

    if ((instruction >> 30) & 1) {
        inst_type = 4;
        opcode = (((instruction >> 25) & 0x1f) << 3) | ((instruction >> 12) & 0x7);
        ra = (instruction >> 20) & 0x1f;
        rb = (instruction >> 15) & 0x1f;
        immd12 = instruction & 0xfff;

        if ((immd12 >> 11) & 1) {
            immd12 = 0xfffffffffffff000 | immd12;
        }
    } else if (((instruction >> 29) & 0x7) == 5) {
        inst_type = 3;
        immd28 = instruction & 0xfffffff;

        if ((immd28 >> 27) & 1) {
            immd28 = 0xfffffffff0000000 | immd28;
        }

        link = (instruction >> 28) & 0x1;
    } else {
        opcode = (instruction >> 25) & 0xf;

        if (opcode == 0) {
            inst_type = 1;
            opcode = instruction & 0x3ff;
            ra = (instruction >> 20) & 0x1f;
            rb = (instruction >> 15) & 0x1f;
            rc = (instruction >> 10) & 0x1f;
        } else {
            inst_type = 2;
            ra = (instruction >> 20) & 0x1f;
            immd20 = instruction & 0xfffff;

            if ((immd20 >> 19) & 1) {
                immd20 = 0xfffffffffff00000 | immd20;
            }
        }
    }
}

void Emulator::execute_instruction() {
    regs[0] = 0;

    switch (inst_type) {
    case 1:
        execute_type_i();
        break;

    case 2:
        execute_type_ii();
        break;

    case 3:
        execute_type_iii();
        break;

    case 4:
        execute_type_iv();
        break;
    }
}

void Emulator::execute_type_i() {
    switch (opcode) {
    case OPCODE_ADD:
        regs[rc] = regs[ra] + regs[rb];
        ip += inst_size;
        break;

    case OPCODE_SUB:
        regs[rc] = regs[ra] - regs[rb];
        ip += inst_size;
        break;

    case OPCODE_AND:
        regs[rc] = regs[ra] & regs[rb];
        ip += inst_size;
        break;

    case OPCODE_OR:
        regs[rc] = regs[ra] | regs[rb];
        ip += inst_size;
        break;

    case OPCODE_XOR:
        regs[rc] = regs[ra] ^ regs[rb];
        ip += inst_size;
        break;

    case OPCODE_SLT:
        regs[rc] = regs[ra] < regs[rb] ? 1 : 0;
        ip += inst_size;
        break;

    case OPCODE_SLTU:
        regs[rc] = ((unsigned) regs[ra]) < ((unsigned) regs[rb]) ? 1 : 0;
        ip += inst_size;
        break;
    }
}

void Emulator::execute_type_ii() {

}

void Emulator::execute_type_iii() {
    if (link) {
        regs[LINK_REGISTER] = ip + inst_size;
    }

    ip = ip + (immd28 << 1);
}

void Emulator::execute_type_iv() {
    switch (opcode) {
    case OPCODE_ADDI:
        regs[ra] = regs[rb] + immd12;
        ip += inst_size;
        break;

    case OPCODE_ANDI:
        regs[ra] = regs[rb] & immd12;
        ip += inst_size;
        break;

    case OPCODE_ORI:
        regs[ra] = regs[rb] | immd12;
        ip += inst_size;
        break;

    case OPCODE_XORI:
        regs[ra] = regs[rb] ^ immd12;
        ip += inst_size;
        break;

    case OPCODE_SLTI:
        regs[ra] = regs[rb] < immd12 ? 1 : 0;
        ip += inst_size;
        break;

    case OPCODE_SLTIU:
        regs[ra] = ((unsigned) regs[rb]) < ((unsigned) immd12) ? 1 : 0;
        ip += inst_size;
        break;

    case OPCODE_LD:
        regs[ra] = memory->read_u64(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LW:
        regs[ra] = memory->read_i32(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LWU:
        regs[ra] = memory->read_u32(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LH:
        regs[ra] = memory->read_i16(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LHU:
        regs[ra] = memory->read_u16(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LB:
        regs[ra] = memory->read_i8(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LBU:
        regs[ra] = memory->read_u8(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_SD:
        memory->write64(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_SW:
        memory->write32(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_SH:
        memory->write16(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_SB:
        memory->write8(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_BEQ:
        if (regs[ra] == regs[rb]) {
            ip += immd12 << 1;
        } else {
            ip += inst_size;
        }
        break;

    case OPCODE_BLT:
        if (regs[ra] < regs[rb]) {
            ip += immd12 << 1;
        } else {
            ip += inst_size;
        }
        break;

    case OPCODE_BLTU:
        if ((unsigned) regs[ra] < (unsigned) regs[rb]) {
            ip += immd12 << 1;
        } else {
            ip += inst_size;
        }
        break;

    case OPCODE_BGE:
        if (regs[ra] >= regs[rb]) {
            ip += immd12 << 1;
        } else {
            ip += inst_size;
        }
        break;

    case OPCODE_BGEU:
        if ((unsigned) regs[ra] >= (unsigned) regs[rb]) {
            ip += immd12 << 1;
        } else {
            ip += inst_size;
        }
        break;

    case OPCODE_JALR:
        ip = regs[LINK_REGISTER];
        break;

    case OPCODE_ECALL:
        eip = ip;
        ip = ebase;
        break;

    case OPCODE_ERET:
        ip = eip;
        break;
    }
}

std::string Emulator::dump_registers() {
    std::stringstream out;

    for (int i = 0; i < 32; ++i) {
        if (i % 4 == 0 && i > 0) {
            out << '\n';
        }

        out << i << ": ";

        if (i < 10) {
            out << ' ';
        }

        out << hex64(regs[i]) << '\t';
    }

    return out.str();
}

std::string Emulator::dump_memory() {
    return memory->dump();
}
