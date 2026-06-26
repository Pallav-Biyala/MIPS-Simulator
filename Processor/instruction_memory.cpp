#include <iostream>
#include <bits/stdc++.h>
#include "Core/instructions.h"
using namespace std;

// now comes IMEM
class Instruction_Memory{
private:
    vector<Instruction> memory;
    vector<string> assembly_lines; // only for representation 

public:
    void addInstruction(const Instruction &inst, const string &line){
        memory.push_back(inst);
        assembly_lines.push_back(line);
    }

    Instruction fetch(int PC) const{
        // so now mips is byte addressable, this means inst. 1--> PC = 4. hence to get index of vector we need to scale it down
        int idx = PC/4;

        if (idx < 0 || idx >= memory.size()){
            throw out_of_range("PC out of instruction memory bounds");
        }

        // now return
        return memory[idx];
    }

    string getInstruction(int PC) const{
        int idx = PC/4;
        if (idx < 0 || idx >= memory.size()){
            throw out_of_range("PC out of instruction memory bounds");
        }
        return assembly_lines[idx];
    }
    
};
