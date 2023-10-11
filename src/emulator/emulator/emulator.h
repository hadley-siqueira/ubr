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
    void execute_type_ii();
    void execute_type_iii();
    void execute_type_iv();

    std::string dump_registers();
    std::string dump_memory();

private:
    void execute_syscall();

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
    int rc;
    int64_t immd12;
    int64_t immd28;
    int64_t immd20;
    bool link;

};

#endif
