#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Now we make ALU but for that we define operations it can do
enum ALUOperation{
    ALU_ADD,
    ALU_SUB,
    ALU_AND,
    ALU_OR,
    ALU_SLT
};

class ALU{
public:
    pair<int, bool> execute(int A, int B, ALUOperation op){
        // so now we just write all operatiosn
        int result = 0;
        bool zero = false;

        switch(op){
            case ALU_ADD:
                result = A+B;
                break;
            
            case ALU_SUB:
                result = A-B;
                break;
            
            case ALU_AND:
                result = A&B;
                break;
            
            case ALU_OR:
                result = A|B;
                break;
            
            case ALU_SLT:
                // slt means set less than. if A<B result = 1 else 0
                if (A < B) result = 1;
                else result = 0;
                break;
        }

        // now zero flag is true when ALU output is 0 
        if (result == 0){
            zero = true;
        }
        return {result, zero};
    }
};


// now using ALUOp we need to know what operation to do. this is handled by ALU Control
class ALUControl{
public:
    ALUOperation decodeALU(int ALUOp, int funct){
        // so if ALUOp is 0, then this means lw and sw. so to find Target address we add base+offset

        if (ALUOp == 0){
            return ALU_ADD;
        }

        // If ALUOp is 1, then this means beq and hence we subtract
        else if (ALUOp == 1){
            return ALU_SUB;
        }

        else{
            // now its R type hence we need to use funct
            switch(funct){
                case 32:
                    // add 
                    return ALU_ADD;
                
                case 34:
                    // sub
                    return ALU_SUB;
                
                case 36:
                    // and
                    return ALU_AND;
                
                case 37:
                    //or
                    return ALU_OR;
                
                case 42:
                    // slt
                    return ALU_SLT;
                
                default:
                    // since our simulator executes basic instructions we would ignore rest instructions
                    throw invalid_argument("Invalid funct field");
            }
        }
    }
};