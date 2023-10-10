#include <fstream>

#include "memory.h"

void Memory::read_binary(std::string path) {
    char c;
    std::ifstream fs;

    fs.open(path);

    while (fs.get(c)) {
        bytes.push_back(c);
    }
}

uint64_t Memory::read_u8(uint64_t address) {
    uint64_t value = 0;

    value = bytes[address] & 0x0ff;

    return value;
}

uint64_t Memory::read_i8(uint64_t address) {
    uint64_t tmp = read_u8(address);
    uint64_t value = 0;

    if ((tmp >> 7) & 1) {
        value = 0xffffffffffffff00;
    }

    value = value | tmp;
    return value;
}

uint64_t Memory::read_u16(uint64_t address) {
    uint64_t value = 0;

    value = bytes[address] & 0xff;
    value = (value << 8) | (bytes[address + 1] & 0xff);

    return value;
}

uint64_t Memory::read_i16(uint64_t address) {
    uint64_t tmp = read_u16(address);
    uint64_t value = 0;

    if ((tmp >> 15) & 1) {
        value = 0xffffffffffff0000;
    }

    value = value | tmp;
    return value;
}

uint64_t Memory::read_u32(uint64_t address) {
    uint64_t value = 0;

    value = bytes[address] & 0xff;
    value = (value << 8) | (bytes[address + 1] & 0xff);
    value = (value << 8) | (bytes[address + 2] & 0xff);
    value = (value << 8) | (bytes[address + 3] & 0xff);

    return value;
}

uint64_t Memory::read_i32(uint64_t address) {
    uint64_t tmp = read_u32(address);
    uint64_t value = 0;

    if ((tmp >> 31) & 1) {
        value = 0xffffffff00000000;
    }

    value = value | tmp;
    return value;
}

uint64_t Memory::read_u64(uint64_t address) {
    uint64_t value = 0;

    value = bytes[address] & 0xff;
    value = (value << 8) | (bytes[address + 1] & 0xff);
    value = (value << 8) | (bytes[address + 2] & 0xff);
    value = (value << 8) | (bytes[address + 3] & 0xff);
    value = (value << 8) | (bytes[address + 4] & 0xff);
    value = (value << 8) | (bytes[address + 5] & 0xff);
    value = (value << 8) | (bytes[address + 6] & 0xff);
    value = (value << 8) | (bytes[address + 7] & 0xff);

    return value;
}

void Memory::write64(uint64_t address, uint64_t value) {
    for (int i = 0; i < 8; ++i) {
        bytes[address + i] = (value >> (64 - (i + 1) * 8)) & 0xff;
    }
}

void Memory::write32(uint64_t address, uint64_t value) {
    for (int i = 0; i < 4; ++i) {
        bytes[address + i] = (value >> (32 - (i + 1) * 8)) & 0xff;
    }
}

void Memory::write16(uint64_t address, uint64_t value) {
    for (int i = 0; i < 2; ++i) {
        bytes[address + i] = (value >> (16 - (i + 1) * 8)) & 0xff;
    }
}

void Memory::write8(uint64_t address, uint64_t value) {
    bytes[address] = value & 0xff;
}
