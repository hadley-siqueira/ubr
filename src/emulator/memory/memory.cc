#include <fstream>
#include <sstream>
#include <iostream>

#include "memory.h"

void Memory::read_binary(std::string path) {
    char c;
    std::ifstream fs;

    fs.open(path);
    bytes.reserve(2048);

    while (fs.get(c)) {
        bytes.push_back(c);
    }

    while (bytes.size() < 2048) {
        bytes.push_back(0);
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

    if (address == 400) {
        std::cout << (char) value;
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

std::string hex8(uint64_t value) {
    std::stringstream ss;

    for (int i = 4; i >= 0; i -= 4) {
        int k = (value >> i) & 0xf;

        if (k < 10) {
            ss << ((char) ('0' + k));
        } else {
            ss << ((char) ('a' + k - 10));
        }
    }

    return ss.str();
}

std::string hex642(uint64_t value) {
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

std::string Memory::dump() {
    std::stringstream out;

    for (int i = 0; i < bytes.size(); i += 16) {
        std::stringstream ss;
        ss << hex642(i) << "  ";

        for (int j = 0; j < 8 && i + j < bytes.size(); ++j) {
            ss << hex8(bytes[i + j]) << ' ';
        }

        ss << ' ';

        for (int j = 8; j < 16 && i + j < bytes.size(); ++j) {
            ss << hex8(bytes[i + j]) << ' ';
        }

        ss << ' ';

        int col = ss.str().size();
        while (col < 68) {
            ++col;
            ss << ' ';
        }

        ss << '|';
        for (int j = 0; j < 16 && i + j < bytes.size(); ++j) {
            if (bytes[i + j] >= 32 && bytes[i + j] <= 126) {
                ss << ((char) (bytes[i + j]));
            } else {
                ss << '.';
            }
        }
        ss << '|';

        ss << '\n';
        out << ss.str();
    }

    return out.str();
}
