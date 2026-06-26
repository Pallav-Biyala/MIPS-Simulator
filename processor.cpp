#include <iostream>
#include <bits/stdc++.h>

#include "alu.cpp"
#include "control_unit.cpp"
#include "data_memory.cpp"
#include "instruction_memory.cpp"
#include "register_file.cpp"
using namespace std;

class Processor{
private:
    // _______________________ ALL Hardware components_____________________________
    Instruction_Memory IMEM; // this handles all the isntructions stored in memory
    Data_Memory DMEM; // this handles all the data stored
    RegisterFile RF; // this tracks all registers in MIPS

    ALU alu; // this perofms alu operations
    ALUControl aluCU; // this tells what opeations to perform
    ControlUnit CU; // this handles control unit

    // ________________________ Extra vairables to keep track of (wires)____________________
    // IF
    int PC; // this tracks the address of next isntruction
    Instruction current_inst; // current isntruction being executed
    
    // ID
    ControlSignals control; // this stores all control signals
    int RD1; // ALU input
    int RD2; /// alu input
    
    // EX
    int ALUResult;
    bool Zero;

    int BTA; // branch target address
    int JTA; // jump target address

    // MEM
    int data_to_be_loaded;

    // now we need to maintain when it has to stop
    bool running = true;

public:
    Processor(){
        PC = 0;
    }

    void loadInstruction(Instruction inst, string line){
        IMEM.addInstruction(inst, line);
    }

    void printRegisters() const{
        RF.printRegisters();
    }

    void IF(){
        current_inst = IMEM.fetch(PC);
        // now we move to next address
        PC = PC + 4;
    }

    void ID(){
        // now we need to decode whole instruction
        control = CU.generate(current_inst.op);

        // now register file reads the rs rt registers
        auto [read1, read2] = RF.read(current_inst.rs, current_inst.rt);

        RD1 = read1;
        RD2 = read2;
    }

    void EX(){
        // so firstly we need to know what ALUOperation we have to do
        ALUOperation op = aluCU.decodeALU(control.ALUOp, current_inst.funct);

        // now know what operation to do so we can send this to ALU to do it
        int second_ALU_input = 0;
        if (control.ALUSrc == 1){
            // Input to ALU is immediate
            second_ALU_input = (int) current_inst.imm;
        }
        else{
            second_ALU_input = RD2;
        }
        
        auto [result, zero] = alu.execute(RD1, second_ALU_input, op);

        ALUResult = result;
        Zero = zero;

        // __________________________________________________________________________//
        // Now in ex we also find JTA and BTA
        // so BTA = (PC+4) + offset*4.
        BTA = PC + ((int)current_inst.imm << 2);

        // JTA = PC first 4 bits + 26 bits<<2
        JTA = (PC & (0xF0000000)) | (current_inst.address<<2);
    }

    void MEM(){
        //_________________________LOAD AND STORE_________________________________
        // so now mem is used only when mem read is 1 or memwrite is 1
        if (control.MemRead){
            // its load. so we need to extract data from memory at location stored in ALUResult
            data_to_be_loaded = DMEM.read(ALUResult);
        }
        else if (control.MemWrite){
            // now we need to store data in rt in address given
            DMEM.write(ALUResult, RD2);
        }
        

        // ________________________ Branch and JUMP__________________________________
        // next thing we do is to check if branch has to be taken or not. if yes, then update pc otw not
        if (control.Branch && Zero){
            // now update PC to BTA
            PC = BTA;
        }

        // check for jump
        if (control.Jump){
            // now update PC to JTA
            PC = JTA;
        }
    }

    void WB(){
        if (!control.RegWrite){
            return;
        }
        // now we either have to load data from memory to register or ALUResult to it. this is defined by memtoreg
        int destination_register = 0;
        if (control.RegDst){
            destination_register = current_inst.rd;
        }
        else{
            destination_register = current_inst.rt;
        }

        int writeData;
        if(control.MemToReg){
            // this means data comes from memroy lw
            writeData = data_to_be_loaded;
        }
        else{
            // this meand data comes form aluresult
            writeData = ALUResult;
        }

        RF.write(destination_register, writeData);
    }

    // now we create a function that does whole CPU Instruction cycle
    void step(){
        IF();
        // check if its halt?
        if (current_inst.op == HALT){
            running = false;
            return;
        }
        ID();
        EX();
        MEM();
        WB();

        
    }

    // now we execute all isntructions
    void run(){
        int cycle = 0;
        while(running){
            cout << "\n========== Cycle " << cycle++ << " ==========\n";
            cout << "PC = " << PC << '\n';
            cout<<"Instruction: "<< IMEM.getInstruction(PC)<<endl;
            step();
            cout << "-------------------------------------\n";
            printRegisters();
        }
        cout << "\nProgram finished successfully.\n";
        cout << "Final Register State:\n";
        RF.printRegisters();
    }
};