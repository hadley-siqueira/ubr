#include <fstream>
#include <sstream>

#include "emulator.h"

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
}

Emulator::~Emulator() {

}

void Emulator::read_binary(std::string path) {
    memory.read_binary(path);
}

void Emulator::tick() {
    fetch_instruction();
    decode_instruction();
    execute_instruction();
}

void Emulator::fetch_instruction() {
    instruction = memory.read_u32(ip);
}

void Emulator::decode_instruction() {
    inst_size = 4;

    if ((instruction >> 30) & 1) {
        inst_type = 0;
        opcode = (((instruction >> 25) & 0x1f) << 3) | ((instruction >> 12) & 0x7);
        ra = (instruction >> 20) & 0x1f;
        rb = (instruction >> 15) & 0x1f;
        immd12 = instruction & 0xfff;

        if ((immd12 >> 11) & 1) {
            immd12 = 0xfffffffffffff000 | immd12;
        }
    }
}

void Emulator::execute_instruction() {
    switch (inst_type) {
    case 0:
        execute_type_i();
        break;
    }
}

void Emulator::execute_type_i() {
    switch (opcode) {
    case 0:
        regs[ra] = regs[rb] + immd12;
        ip += inst_size;
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
