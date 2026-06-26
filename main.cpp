#include <iostream>
#include <bits/stdc++.h>

#include "assembler.cpp"
#include "Processor/processor.cpp"

using namespace std;

int main()
{
    Processor cpu;
    Assembler assembler;

    // so to get the program file, we use:
    ifstream file("program.asm");

    if (!file.is_open()){
        cout<<"Couldn't open the file";
        return 1;
    }

    string line;
    while (getline(file, line)){

        // so firstly we ignore blank lines
        if (line.empty()){
            continue;
        }

        Instruction inst = assembler.parseInstruction(line);
        cpu.loadInstruction(inst, line);
    }

    cpu.run();
    return 0;
}
