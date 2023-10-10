#ifndef UBR_MEMORY_H
#define UBR_MEMORY_H

#include <cstdint>
#include <string>
#include <vector>

class Memory {
public:
    void read_binary(std::string path);

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

private:
    std::vector<uint8_t> bytes;
};

#endif
