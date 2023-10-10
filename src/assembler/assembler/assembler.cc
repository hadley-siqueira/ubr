#include <sstream>
#include <fstream>
#include "assembler.h"
#include "../parser/parser.h"
#include "../binary_output/binary_output.h"

void Assembler::read(std::string path) {
    Parser p;

    mod = p.parse(path);
}

void Assembler::generate_output(std::string path) {
    BinaryOutput out;

    mod->first_pass();
    mod->write_to(&out);
    out.write(path);
}
