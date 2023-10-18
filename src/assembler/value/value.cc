#include <map>
#include <sstream>
#include <iostream>
#include "value.h"
#include "../symbol_table/symbol_table.h"
#include "../../opcodes/opcodes.h"

std::map<std::string, int> regs_map = {
    {"0", 0},
    {"1", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"11", 11},
    {"12", 12},
    {"13", 13},
    {"14", 14},
    {"15", 15},
    {"16", 16},
    {"17", 17},
    {"18", 18},
    {"19", 19},
    {"20", 20},
    {"21", 21},
    {"22", 22},
    {"23", 23},
    {"24", 24},
    {"25", 25},
    {"26", 26},
    {"27", 27},
    {"28", 28},
    {"29", 29},
    {"30", 30},
    {"31", 31},
    {"a0", REG_A0},
    {"a1", REG_A1},
    {"a2", REG_A2},
    {"a3", REG_A3},
    {"a4", REG_A4},
    {"a5", REG_A5},
    {"a6", REG_A6},
    {"a7", REG_A7},
    {"t0", REG_T0},
    {"t1", REG_T1},
    {"t2", REG_T2},
    {"t3", REG_T3},
    {"t4", REG_T4},
    {"t5", REG_T5},
    {"t6", REG_T6},
    {"t7", REG_T7},
    {"a0", REG_A0},
    {"v0", REG_V0},
    {"sp", REG_SP},
    {"lr", LINK_REGISTER}
};

Value::Value(int kind) {
    this->kind = kind;
}

Value::Value(int kind, std::string value) {
    this->kind = kind;
    this->value = value;
}

void Value::set_value(std::string value) {
    this->value = value;
}

int Value::to_int() {
    int r = 0;
    std::stringstream ss;
    Symbol* sym;
    Label* label;

    switch (kind) {
    case VAL_REG:
        r = regs_map[value];
        break;

    case VAL_NUMBER:
        ss << value;
        ss >> r;
        break;

    case VAL_ID:
        SymbolTable* symtab = get_symbol_table();
        sym = symtab->resolve(value);

        if (sym && sym->get_kind() == SYM_LABEL) {
            label = (Label*) sym->get_descriptor();
            return label->get_offset();
        }

        break;
    }

    return r;
}

int Value::get_kind() {
    return kind;
}
