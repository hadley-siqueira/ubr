#include <fstream>
#include <sstream>
#include <iostream>

#include "processor.h"
#include "../../opcodes/opcodes.h"
#include "../../utils/utils.h"

Processor::Processor() {
    ip = 0;

    for (int i = 0; i < 32; ++i) {
        regs[i] = 0;
    }

    regs[30] = 2040;
}

Processor::~Processor() {

}

void Processor::tick() {
    fetch_instruction();
    decode_instruction();
    execute_instruction();
}

void Processor::fetch_instruction() {
    instruction = memory_manager->read_u32(ip);
}

void Processor::decode_instruction() {
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

void Processor::execute_instruction() {
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

void Processor::execute_type_i() {
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

void Processor::execute_type_ii() {
    switch (opcode) {
    case OPCODE_LUI:
        regs[ra] = immd20 << 12;
        ip += inst_size;
        break;

    case OPCODE_AUIPC:
        regs[ra] = (immd20 << 12) + ip;
        ip += inst_size;
        break;
    }
}

void Processor::execute_type_iii() {
    if (link) {
        regs[LINK_REGISTER] = ip + inst_size;
    }

    ip = ip + (immd28 << 1);
}

void Processor::execute_type_iv() {
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
        regs[ra] = memory_manager->read_u64(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LW:
        regs[ra] = memory_manager->read_i32(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LWU:
        regs[ra] = memory_manager->read_u32(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LH:
        regs[ra] = memory_manager->read_i16(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LHU:
        regs[ra] = memory_manager->read_u16(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LB:
        regs[ra] = memory_manager->read_i8(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_LBU:
        regs[ra] = memory_manager->read_u8(regs[rb] + immd12);
        ip += inst_size;
        break;

    case OPCODE_SD:
        memory_manager->write64(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_SW:
        memory_manager->write32(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_SH:
        memory_manager->write16(regs[rb] + immd12, regs[ra]);
        ip += inst_size;
        break;

    case OPCODE_SB:
        memory_manager->write8(regs[rb] + immd12, regs[ra]);
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
        ip = regs[rb] + (immd12 << 1);
        regs[ra] = ip + 4;
        break;

    case OPCODE_ECALL:
        csr[EIP] = ip;
        ip = csr[EBASE];
        break;

    case OPCODE_ERET:
        ip = csr[EIP];
        break;

    case OPCODE_CSRR:
        regs[ra] = csr[immd12 & 0xfff];
        ip += inst_size;
        break;

    case OPCODE_CSRW:
        csr[immd12 & 0xfff] = regs[ra];
        ip += inst_size;
        break;
    }
}

std::string Processor::dump_registers() {
    std::stringstream out;

    out << "ip: " << hex64(ip);
    out << "    eip: " << hex64(csr[EIP]) << '\n';
    out << "ebase: " << hex64(csr[EBASE]) << '\n';

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

MemoryManager* Processor::get_memory_manager() const {
    return memory_manager;
}

void Processor::set_memory_manager(MemoryManager* value) {
    memory_manager = value;
}
