#include <iostream>
#include "emulator/emulator.h"

int main(int argc, char** argv) {
    Emulator emulator;

    std::cout << emulator.dump_registers() << std::endl;
    return 0;
}
