#ifndef UBR_EMULATOR_H
#define UBR_EMULATOR_H

#include <string>
#include <cstdint>
#include "../memory/memory.h"
#include "../processor/processor.h"
#include "../memory_manager/memory_manager.h"

class Emulator {
public:
    Emulator();
    ~Emulator();

public:
    void read_binary(std::string path);
    void run(uint64_t iters=0);
    std::string dump_memory();
    std::string dump_registers();

private:
    Memory* memory;
    MemoryManager* memory_manager;
    Processor* processor;
};

#endif
