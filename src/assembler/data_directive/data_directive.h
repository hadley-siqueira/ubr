#ifndef DATA_DIRECTIVE_H
#define DATA_DIRECTIVE_H

#include <vector>

#include "../command/command.h"
#include "../token/token.h"

class DataDirective : public Command {
public:
    DataDirective(int kind);

public:
    void add_value(Token token);
    void write_to(BinaryOutput* value);
    void write_byte_directive(BinaryOutput* value);
    void write_int_directive(BinaryOutput* value);
    int get_size();

private:
    std::vector<Token> values;
};

#endif
