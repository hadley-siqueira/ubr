#include <iostream>
#include <sstream>

#include "parser.h"
#include "../scanner/scanner.h"
#include "../module/module.h"
#include "../data_directive/data_directive.h"
#include "../align_directive/align_directive.h"
#include "../label/label.h"
#include "../instruction/instruction.h"
#include "../symbol_table/symbol_table.h"

Parser::Parser() {
    for (int i = 0; i < 32; ++i) {
        std::stringstream s;
        s << i;
        regs_map[s.str()] = i;
    }

    opcodes_map["add"] = CMD_INST_ADD;
    opcodes_map["sub"] = CMD_INST_SUB;

    opcodes_map["and"] = CMD_INST_AND;
    opcodes_map["or"] = CMD_INST_OR;
    opcodes_map["xor"] = CMD_INST_XOR;

    opcodes_map["slt"] = CMD_INST_SLT;
    opcodes_map["sltu"] = CMD_INST_SLTU;

    opcodes_map["beq"] = CMD_INST_BEQ;
    opcodes_map["bne"] = CMD_INST_BNE;
    opcodes_map["blt"] = CMD_INST_BLT;
    opcodes_map["bge"] = CMD_INST_BGE;
    opcodes_map["bltu"] = CMD_INST_BLTU;
    opcodes_map["bgeu"] = CMD_INST_BGE;

    opcodes_map["j"] = CMD_INST_J;
    opcodes_map["jal"] = CMD_INST_JAL;
    opcodes_map["jalr"] = CMD_INST_JALR;

    opcodes_map["ld"] = CMD_INST_LD;
    opcodes_map["lw"] = CMD_INST_LW;
    opcodes_map["lwu"] = CMD_INST_LWU;
    opcodes_map["lh"] = CMD_INST_LH;
    opcodes_map["lhu"] = CMD_INST_LHU;
    opcodes_map["lb"] = CMD_INST_LB;
    opcodes_map["lbu"] = CMD_INST_LBU;

    opcodes_map["sd"] = CMD_INST_SD;
    opcodes_map["sw"] = CMD_INST_SW;
    opcodes_map["sh"] = CMD_INST_SH;
    opcodes_map["sb"] = CMD_INST_SB;

    opcodes_map["addi"] = CMD_INST_ADDI;
    opcodes_map["andi"] = CMD_INST_ANDI;
    opcodes_map["ori"] = CMD_INST_ORI;
    opcodes_map["xori"] = CMD_INST_XORI;
    opcodes_map["slti"] = CMD_INST_SLTI;
    opcodes_map["sltiu"] = CMD_INST_SLTIU;

    opcodes_map["syscall"] = CMD_INST_ECALL;
}

Module* Parser::parse(std::string path) {
    Scanner sc;

    idx = 0;
    tokens = sc.read(path);

    // for (int i = 0; i < tokens.size(); ++i) {
    //     std::cout << tokens[i].to_str() << '\n';
    // }

    return parse_module();
}

Module* Parser::parse_module() {
    mod = new Module();

    while (true) {
        if (lookahead(TK_DOT)) {
            mod->add_to_section(parse_directive());
        } else if (lookahead(TK_ID)) {
            mod->add_to_section(parse_label_or_instruction());
        } else {
            break;
        }
    }

    return mod;
}

Command* Parser::parse_directive() {
    Command* inst = nullptr;
    expect(TK_DOT);

    if (lookahead("byte")) {
        inst = parse_byte_directive();
    } else if (lookahead("int")) {
        inst = parse_int_directive();
    } else if (lookahead("string")) {
        parse_string_directive();
    } else if (lookahead("align")) {
        inst = parse_align_directive();
    }

    return inst;
}

Command* Parser::parse_align_directive() {
    std::stringstream ss;
    int value;

    expect("align");
    expect(TK_NUMBER);

    ss << matched.get_lexeme();
    ss >> value;

    return new AlignDirective(value);
}

Command* Parser::parse_byte_directive() {
    DataDirective* dir = new DataDirective(CMD_BYTE_DIRECTIVE);
    expect("byte");

    dir->add_value(parse_byte_literal());

    while (match(TK_COMMA)) {
        dir->add_value(parse_byte_literal());
    }

    return dir;
}

Command* Parser::parse_int_directive() {
    DataDirective* dir = new DataDirective(CMD_INT_DIRECTIVE);
    expect("int");

    dir->add_value(parse_int_literal());

    while (match(TK_COMMA)) {
        dir->add_value(parse_int_literal());
    }

    return dir;
}

void Parser::parse_string_directive() {
    expect("string");
    expect(TK_STRING);
}

Token Parser::parse_byte_literal() {
    expect(TK_NUMBER);
    return matched;
}

Token Parser::parse_int_literal() {
    expect(TK_NUMBER);
    return matched;
}

Command* Parser::parse_label_or_instruction() {
    std::string id = parse_id();

    if (match(TK_COLON)) {
        Label* label = new Label(id);
        Section* section = mod->get_current_section();

        get_symbol_table()->define_label(section, label);
        return label;
    } 

    return parse_instruction(id);
}

Command* Parser::parse_instruction(std::string op) {
    switch (opcodes_map[op]) {
    case CMD_INST_ADD:
    case CMD_INST_SUB:
    case CMD_INST_AND:
    case CMD_INST_OR:
    case CMD_INST_XOR:
    case CMD_INST_SLT:
    case CMD_INST_SLTU:
        return parse_instruction_reg_reg_reg(opcodes_map[op]);

    case CMD_INST_BEQ:
    case CMD_INST_BNE
    case CMD_INST_BLT:
    case CMD_INST_BGE:
    case CMD_INST_BLTU:
    case CMD_INST_BGEU:
    case CMD_INST_JALR:
        return parse_instruction_reg_reg_immd(opcodes_map[op]);

    case CMD_INST_J:
    case CMD_INST_JAL:
        return parse_jump_instruction(opcodes_map[op]);

    case CMD_INST_LD:
    case CMD_INST_LW:
    case CMD_INST_LWU:
    case CMD_INST_LH:
    case CMD_INST_LHU:
    case CMD_INST_LB:
    case CMD_INST_LBU:
        return parse_instruction_mem(opcodes_map[op]);

    case CMD_INST_SD:
    case CMD_INST_SW:
    case CMD_INST_SH:
    case CMD_INST_SB:
        return parse_instruction_mem(opcodes_map[op]);

    case CMD_INST_ADDI:
    case CMD_INST_ANDI:
    case CMD_INST_ORI:
    case CMD_INST_XORI:
    case CMD_INST_SLTI:
    case CMD_INST_SLTIU:
    case CMD_INST_ECALL:
        return parse_instruction_reg_reg_immd(opcodes_map[op]);
    }

    return nullptr;
}

Command* Parser::parse_instruction_reg_reg_reg(int kind) {
    Instruction* inst = new Instruction(kind);

    inst->set_dest(parse_operand(true));
    expect(TK_COMMA);

    inst->set_src1(parse_operand(true));
    expect(TK_COMMA);

    inst->set_src2(parse_operand(true));
    return inst;
}

Command* Parser::parse_instruction_reg_reg_immd(int kind) {
    Instruction* inst = new Instruction(kind);

    inst->set_dest(parse_operand(true));
    expect(TK_COMMA);

    inst->set_src1(parse_operand(true));
    expect(TK_COMMA);

    inst->set_src2(parse_operand());
    return inst;
}

Value* Parser::parse_operand(bool is_register) {
    Value* r = nullptr;

    if (lookahead(TK_ID)) {
        if (is_register) {
            r = new Value(VAL_REG, parse_id());
        } else {
            r = new Value(VAL_ID, parse_id());
        }
    } else if (match(TK_MODULO)) {
        expect(TK_NUMBER);

        if (regs_map.count(matched.get_lexeme()) > 0) {
            r = new Value(VAL_REG, matched.get_lexeme());
        }
    } else if (match(TK_NUMBER)) {
        r = new Value(VAL_NUMBER, matched.get_lexeme());
    } else if (match(TK_MINUS)) {
        std::stringstream ss;
        expect(TK_NUMBER);

        ss << '-' << matched.get_lexeme();
        r = new Value(VAL_NUMBER, ss.str());
    }

    return r;
}

Command* Parser::parse_instruction_mem(int kind) {
    Instruction* inst = new Instruction(kind);

    inst->set_dest(parse_operand(true));
    expect(TK_COMMA);

    inst->set_src2(parse_operand());
    expect(TK_LPAREN);

    inst->set_src1(parse_operand(true));
    expect(TK_RPAREN);

    return inst;
}

Command* Parser::parse_jump_instruction(int kind) {
    Instruction* inst = new Instruction(kind);

    inst->set_src1(parse_operand());
    return inst;
}

std::string Parser::parse_id() {
    std::stringstream id;
    expect(TK_ID);
    id << matched.get_lexeme();

    while (match(TK_DOT)) {
        expect(TK_ID);
        id << '.' << matched.get_lexeme();
    }

    if (match(TK_HASH)) {
        expect(TK_ID);
        id << "#" << matched.get_lexeme();
    }

    if (match(TK_LT)) {
        id << '<' << parse_id_list();
        expect(TK_GT);
        id << '>';
    }

    if (match(TK_LPAREN)) {
        id << '(' << parse_id_list();
        expect(TK_RPAREN);
        id << ')';
    }

    return id.str();
}

std::string Parser::parse_id_list() {
    std::stringstream l;

    l << parse_id();

    while (match(TK_COMMA)) {
        l << ", " << parse_id();
    }

    return l.str();
}

void Parser::expect(int kind) {
    if (match(kind)) {
        return;
    }

    //log_error_and_exit(error_unexpected_token(path, tokens[idx]));
    std::cout << "expect error\n";
    exit(0);
}

void Parser::expect(std::string lexeme) {
    if (match(lexeme)) {
        return;
    }

    //log_error_and_exit(error_unexpected_token(path, tokens[idx]));
    std::cout << "expect error\n";
    exit(0);
}

bool Parser::match(int kind) {
    if (lookahead(kind)) {
        matched = tokens[idx];
        advance();
        return true;
    }

    return false;
}

bool Parser::match(std::string lexeme) {
    if (lookahead(lexeme)) {
        matched = tokens[idx];
        advance();
        return true;
    }

    return false;
}

bool Parser::lookahead(int kind) {
    return tokens[idx].get_kind() == kind;
}

bool Parser::lookahead(std::string lexeme) {
    return tokens[idx].get_lexeme() == lexeme;
}

void Parser::advance() {
    if (idx < tokens.size()) {
        ++idx;
    }
}

