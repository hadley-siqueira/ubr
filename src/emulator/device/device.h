#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>

class Device {
public:
    Device();
    uint64_t get_base_address();
    uint64_t get_size();
    void write64(uint64_t address, uint64_t value);
};

#endif
