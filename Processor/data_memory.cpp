#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// now comes Data Memory
class Data_Memory{
private:
    vector<int> memory;
public:
    Data_Memory(){
        // so lets say our memory can hold 1024 words
        memory.assign(1024, 0);
    }

    int read(int address){
        if(address % 4 != 0)
            throw invalid_argument("Unaligned memory access");
        // so now we have address which is again byte addressable hence to get index divide by 4
        int idx = address/4;

        // now check bounds
        if (idx < 0 || idx >= (int)memory.size()){
            throw out_of_range("Address Not Found");
        }

        // return data
        return memory[idx];
    }

    void write(int address, int data){
        if(address % 4 != 0)
            throw invalid_argument("Unaligned memory access");
        // so now we have address which is again byte addressable hence to get index divide by 4
        int idx = address/4;

        // now check bounds
        if (idx < 0 || idx >= (int)memory.size()){
            throw out_of_range("Address Not Found");
        }

        // write data
        memory[idx] = data;
    }
};