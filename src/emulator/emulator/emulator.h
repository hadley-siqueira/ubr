#ifndef UBR_EMULATOR_H
#define UBR_EMULATOR_H

#include <string>
#include <cstdint>
#include "../memory/memory.h"

class Emulator {
public:
    Emulator();
    ~Emulator();

public:
    void read_binary(std::string path);

    void tick();
    void fetch_instruction();
    void decode_instruction();
    void execute_instruction();

    void execute_type_i();

    std::string dump_registers();

private:
    uint64_t ip;
    int64_t regs[32];
    Memory memory;
    uint64_t clock;
    uint32_t instruction;

    int inst_type;
    int inst_size;
    int opcode;
    int ra;
    int rb;
    uint64_t immd12;

};

#endif
