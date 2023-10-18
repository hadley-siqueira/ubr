#include "memory_manager.h"

const int MAX_ADDR = 1024 * 1024 * 128;

uint64_t MemoryManager::read_u8(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_u8(address);
    }
}

uint64_t MemoryManager::read_i8(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_i8(address);
    }
}

uint64_t MemoryManager::read_u16(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_u16(address);
    }
}

uint64_t MemoryManager::read_i16(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_i16(address);
    }
}

uint64_t MemoryManager::read_u32(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_u32(address);
    }
}

uint64_t MemoryManager::read_i32(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_i32(address);
    }
}

uint64_t MemoryManager::read_u64(uint64_t address) {
    if (address < MAX_ADDR) {
        return memory->read_u64(address);
    }
}

void MemoryManager::write64(uint64_t address, uint64_t value) {
    if (address < MAX_ADDR) {
        memory->write64(address, value);
    }
}

void MemoryManager::write32(uint64_t address, uint64_t value) {
    if (address < MAX_ADDR) {
        memory->write32(address, value);
    }
}

void MemoryManager::write16(uint64_t address, uint64_t value) {
    if (address < MAX_ADDR) {
        memory->write16(address, value);
    }
}

void MemoryManager::write8(uint64_t address, uint64_t value) {
    if (address < MAX_ADDR) {
        memory->write8(address, value);
    }
}

Memory* MemoryManager::get_memory() const {
    return memory;
}

void MemoryManager::set_memory(Memory* value) {
    memory = value;
}
