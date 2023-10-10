#ifndef HIVEK_ASSEMBLER_H
#define HIVEK_ASSEMBLER_H

#include <cstdint>
#include "../../opcodes/opcodes.h"
#include "../module/module.h"

class Assembler {
public:
    void read(std::string path);
    void generate_output(std::string path);

private:
    Module* mod;
    std::vector<char> output;
};

#endif
