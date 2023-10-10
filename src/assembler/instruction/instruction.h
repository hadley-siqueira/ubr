#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../command/command.h"
#include "../value/value.h"
#include "../../opcodes/opcodes.h"

class Instruction : public Command {
public:
    Instruction(int kind);
    ~Instruction();

public:
    void write_to(BinaryOutput* value);
    void write_binary_type_i(BinaryOutput* value, int func);
    void write_binary_type_iv(BinaryOutput* value, int opcode);
    void write_binary_type_iv_i(BinaryOutput* value, int opcode);
    int get_binary_type_i(int func);
    int get_binary_type_iv(int opcode);
    int get_binary_type_iv_i(int opcode);
    int get_size();

public:
    void set_dest(Value* r);
    void set_src1(Value* r);
    void set_src2(Value* r);

private:
    Value* dest;
    Value* src1;
    Value* src2;
};

#endif
