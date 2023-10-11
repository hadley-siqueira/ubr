#include <iostream>
#include "emulator/emulator.h"

int main(int argc, char** argv) {
    Emulator emulator;

    emulator.read_binary(argv[1]);

    for (int i = 0; i < 1500; ++i) {
        emulator.tick();
    }

//    std::cout << emulator.dump_registers() << std::endl;
//    std::cout << emulator.dump_memory() << std::endl;
    return 0;
}
