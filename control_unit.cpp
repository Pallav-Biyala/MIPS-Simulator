#include <iostream>
#include <bits/stdc++.h>
#include "instructions.h"
using namespace std;

// now comes Control Signals
struct ControlSignals{
    bool RegDst; // RegDst = 1 means rd and 0 means rt (destination register where to write)
    bool ALUSrc; // ALUSrc = 1 means input to ALU is imm and 0 means register rt
    bool MemToReg; // MemtoReg = 1 means memory data should be written to register and 0 means ALU data is to be written to register
    bool RegWrite; // if 1 means write register allowed
    bool MemRead; // if 1 means memory read allowed
    bool MemWrite; // if 1 means memory write allowed
    bool Branch; // branch to be taken or not? if beq then it is 1
    bool Jump; // need to jump or not? if j then it is 1

    int ALUOp; // what type of instruction is. 
    // if 0 it means lw/sw hence add base+offset to find address
    // if 1 it means beq hence subtract A-B to know they are equal or not
    // if 2 means they are R Type
};

class ControlUnit{
public:
    ControlSignals generate(Opcode Op){
        ControlSignals signal;

        switch(Op){
            // so ADD and SUB same control signals as both are R Type
            case ADD:
            case SUB:
                signal.RegDst = true; // r type
                signal.ALUSrc = false;
                signal.MemToReg = false;
                signal.RegWrite = true;
                signal.MemRead = false;
                signal.MemWrite = false;
                signal.Branch = false;
                signal.Jump = false;
                signal.ALUOp = 2;
                break;
            
            case LW:
                signal.RegDst = false; // as now its I type
                signal.ALUSrc = true; // I type
                signal.MemToReg = true;
                signal.RegWrite = true;
                signal.MemRead = true;
                signal.MemWrite = false;
                signal.Branch = false;
                signal.Jump = false;
                signal.ALUOp = 0;
                break;
            
            case SW:
                signal.RegDst = false; // dont care 
                signal.ALUSrc = true; // I type
                signal.MemToReg = false; // dont care
                signal.RegWrite = false;
                signal.MemRead = false;
                signal.MemWrite = true;
                signal.Branch = false;
                signal.Jump = false;
                signal.ALUOp = 0;
                break;
            
            case ADDI:
                signal.RegDst = false; // as now its I type
                signal.ALUSrc = true; // I type
                signal.MemToReg = false;
                signal.RegWrite = true;
                signal.MemRead = false;
                signal.MemWrite = false;
                signal.Branch = false;
                signal.Jump = false;
                signal.ALUOp = 0; // as we just have to add and in 0 that what its doing
                break;
            
            case BEQ:
                signal.RegDst = false; // as now its I type
                signal.ALUSrc = false; // As we need to subtract boht reifsters and comapre them
                signal.MemToReg = false;
                signal.RegWrite = false;
                signal.MemRead = false;
                signal.MemWrite = false;
                signal.Branch = true;
                signal.Jump = false;
                signal.ALUOp = 1;
                break;
            
            case J:
                signal.RegDst = false; // dont care
                signal.ALUSrc = false; // as J doesnt use ALU so dont care
                signal.MemToReg = false;
                signal.RegWrite = false;
                signal.MemRead = false;
                signal.MemWrite = false;
                signal.Branch = false;
                signal.Jump = true;
                signal.ALUOp = 0; // dont care as it dont use ALU
                break;
            
            case HALT:
                signal.RegDst = false;
                signal.ALUSrc = false;
                signal.MemToReg = false;
                signal.RegWrite = false;
                signal.MemRead = false;
                signal.MemWrite = false;
                signal.Branch = false;
                signal.Jump = false;
                signal.ALUOp = 0;
                break;
        }
        return signal;
    }
};