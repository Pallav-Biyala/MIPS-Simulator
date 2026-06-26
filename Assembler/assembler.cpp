#include <iostream>
#include <bits/stdc++.h>
#include "Core/instructions.h"
#include "Core/registers.h"

using namespace std;

class Assembler{
private:
    const unordered_map <string, Opcode> OpcodeMap = {
        {"add", ADD},
        {"sub", SUB},
        {"addi", ADDI},
        {"lw", LW},
        {"sw", SW},
        {"beq",BEQ},
        {"j", J},
        {"halt", HALT}
    };

    string getNextToken(const string &line, int &i){
        // slip commas and spaces
        while (i<line.size() && (line[i] == ',' || line[i] == ' ' || line[i] == '\t'|| line[i] == '(')){
            i++;
        }

        string token;
        while (i<line.size() && line[i] != ',' && line[i] != ' ' && line[i] != ')'){
            token += line[i];
            i++;
        }
        return token;
    }

public:
    Instruction parseInstruction(string line){
        // so now line looks like add $t0, $t1, $t2. so we need to split it
        Instruction inst;

        // first comes opcode
        int i = 0;
        string operation = getNextToken(line, i);
        // .at makes sure that if operation doesnt matches our map, it throws error
        inst.op = OpcodeMap.at(operation);

        // now rest depends if its R Type j type or I type
        if (inst.op == ADD || inst.op == SUB){
            // so now type is add rd, rs, rt
            inst.rd = RegisterMap.at(getNextToken(line, i));
            inst.rs = RegisterMap.at(getNextToken(line, i));
            inst.rt = RegisterMap.at(getNextToken(line, i)); 
            
            if (inst.op == ADD){
                inst.funct = 32;
            }
            else{
                inst.funct = 34;
            }
        }

        else if (inst.op == ADDI){
            // so now type is addi rt, rs, imm
            inst.rt = RegisterMap.at(getNextToken(line, i));
            inst.rs = RegisterMap.at(getNextToken(line, i)); 
            inst.imm = stoi(getNextToken(line, i));
        }

        else if(inst.op == LW || inst.op == SW){
            // now lw/sw is: lw rt, imm(rs)
            inst.rt = RegisterMap.at(getNextToken(line, i));
            inst.imm = stoi(getNextToken(line, i));
            inst.rs = RegisterMap.at(getNextToken(line, i));
        }

        else if (inst.op == BEQ){
            // now its type is beq rs, rt, imm
            inst.rs = RegisterMap.at(getNextToken(line, i));
            inst.rt = RegisterMap.at(getNextToken(line, i)); 
            inst.imm = stoi(getNextToken(line, i));
        }

        else if (inst.op == J){
            // j type just have address
            inst.address = stoi(getNextToken(line, i));
        }

        else{
            // its halt
        }
        return inst;
    }
};
