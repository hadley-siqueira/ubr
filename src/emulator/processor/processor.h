#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>
#include <string>
#include "../memory_manager/memory_manager.h"

class Processor {
public:
    Processor();
    ~Processor();

public:
    void tick();
    void fetch_instruction();
    void decode_instruction();
    void execute_instruction();

    void execute_type_i();
    void execute_type_ii();
    void execute_type_iii();
    void execute_type_iv();

    std::string dump_registers();

    MemoryManager* get_memory_manager() const;
    void set_memory_manager(MemoryManager* value);

private:
    MemoryManager* memory_manager;
    uint64_t cycles;

    // used to track state
    uint64_t ip;
    int64_t regs[32];
    uint64_t csr[4096];

    // used for decoding
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
