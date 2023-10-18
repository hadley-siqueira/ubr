#include <iostream>
#include "emulator/emulator.h"

int main(int argc, char** argv) {
    Emulator emulator;

    emulator.read_binary(argv[1]);

    emulator.run(1500);

    std::cout << emulator.dump_registers() << std::endl;
    std::cout << emulator.dump_memory() << std::endl;
    return 0;
}
