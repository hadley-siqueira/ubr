#ifndef ALIGN_DIRECTIVE_H
#define ALIGN_DIRECTIVE_H

#include "../command/command.h"

class AlignDirective : public Command {
public:
    AlignDirective();
    AlignDirective(int value);

public:
    void set_value(int v);
    int get_value();
    void write_to(BinaryOutput* value);

private:
    int value;
};

#endif
