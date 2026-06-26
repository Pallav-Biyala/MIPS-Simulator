#pragma once
#include <cstdint>

enum Opcode{
    ADD,
    SUB,
    ADDI,
    LW,
    SW,
    BEQ,
    J, 
    HALT
};

// so lets represent instruction
struct Instruction{
    Opcode op = HALT;
    int rs = 0;
    int rt = 0;
    int rd = 0;
    int funct = 0;
    int16_t imm = 0;
    int address = 0;
};
