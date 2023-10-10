#include <iostream>
#include "emulator/emulator.h"

int main(int argc, char** argv) {
    Emulator emulator;

    emulator.read_binary(argv[1]);
    emulator.tick();
    std::cout << emulator.dump_registers() << std::endl;
    return 0;
}
