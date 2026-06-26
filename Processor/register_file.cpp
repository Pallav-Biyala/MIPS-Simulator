#include <iostream>
#include <bits/stdc++.h>
#include "Core/registers.h"
using namespace std;

// so we consider 32 bit address
class RegisterFile{
private:
    vector<int> registers;
    vector<bool> touched;
    
public:
    RegisterFile(){
        registers.assign(32,0);
        touched.assign(32, false);
    }

    pair<int, int> read(int rs, int rt) const{
        if(rs < 0 || rs >= 32 || rt < 0 || rt >= 32){
            // since we have only 32 registers from 0 to 31 in mips 
            throw out_of_range("Invalid register number");
        }  
        
        // here we used two outputs because if we see register file, it has outputs as RD1 and RD2. these represent that
        return {registers[rs], registers[rt]};
    }

    void write(int rd, int data){
        if(rd < 0 || rd >= 32){
            throw out_of_range("Invalid register number");
        }

        if (rd == 0){
            // as $0 cant be written
            return;
        }
        
        touched[rd] = true;
        registers[rd] = data;
    }

    void printRegisters() const{ 
        for (int i = 0; i<32; ++i){
            if (touched[i])
                cout<<RegisterNames[i]<<" = "<<registers[i]<<endl;
        }
    }
};
