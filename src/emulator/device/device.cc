#include "device.h"
#include <iostream>

const int MAX_ADDR = 1024 * 1024 * 128;

Device::Device() {

}

uint64_t Device::get_base_address() {
    uint64_t addr = -1;
    addr -= 32;
    return addr;
}

uint64_t Device::get_size() {
    return 32;
}

void Device::write64(uint64_t address, uint64_t value) {
    std::cout << (char) value;
}
