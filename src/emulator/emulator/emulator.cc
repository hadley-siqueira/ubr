#include <fstream>
#include <sstream>
#include <iostream>

#include "emulator.h"
#include "../../opcodes/opcodes.h"

Emulator::Emulator() {
    processor = new Processor();
    memory = new Memory();
    memory_manager = new MemoryManager();

    processor->set_memory_manager(memory_manager);
    memory_manager->set_memory(memory);
}

Emulator::~Emulator() {
    delete processor;
    delete memory;
    delete memory_manager;
}

void Emulator::read_binary(std::string path) {
    memory->read_binary(path);
}

void Emulator::run(uint64_t iters) {
    if (iters == 0) {
        while (true) {
            processor->tick();
        }
    } else {
        for (int i = 0; i < iters; ++i) {
            processor->tick();
        }
    }
}

std::string Emulator::dump_memory() {
    return memory->dump();
}

std::string Emulator::dump_registers() {
    return processor->dump_registers();
}


