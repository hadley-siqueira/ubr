#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "../memory/memory.h"
#include "../device/device.h"

class MemoryManager {
public:
    uint64_t read_u8(uint64_t address);
    uint64_t read_i8(uint64_t address);

    uint64_t read_u16(uint64_t address);
    uint64_t read_i16(uint64_t address);

    uint64_t read_u32(uint64_t address);
    uint64_t read_i32(uint64_t address);

    uint64_t read_u64(uint64_t address);

    void write64(uint64_t address, uint64_t value);
    void write32(uint64_t address, uint64_t value);
    void write16(uint64_t address, uint64_t value);
    void write8(uint64_t address, uint64_t value);

    Memory* get_memory() const;
    void set_memory(Memory* value);

    int devices_count();
    void add_device(Device* device);

private:
    Memory* memory;
    std::vector<Device*> devices;
};

#endif
