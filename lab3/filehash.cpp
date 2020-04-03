// Made by Bronnikov Max

// compile: g++ -std=c++11 -Wall -pedantic Keccak/Keccak.cpp filehash.cpp -o run
// run: ./run

#include <string>
#include <iostream>
#include <vector>
#include "Keccak/Keccak.h"

using namespace std;

// Note: if need SHA-3 - use 0x06 delimeter, if classic Keccak1600 - use 0x01, if some exotik - whatever you want


int main(){
    Keccak1600 hasher(72*8, 128*8, 0x06); // Classic SHA-3-512
    // path to all another files here:
    const char* path_to_file = "documentation/Keccak-reference-3.0.pdf";
    vector<uint8_t> output;
    hasher.file_hash(path_to_file, output);

    cout << "File \"" << path_to_file << "\" Hash:" << endl;
    cout << "===========================================" << endl;
    for(uint8_t i = 0; i < 64; ++i){
        cout << "0x";
        if(output[i] < 16){
            cout << "0";
        }
        cout << hex << int(output[i]) << ' ';
    }
    cout << endl;
    cout << "===========================================" << endl;

    cout << "Program ends! Made by Bronnikov Max!" << endl;
    return 0;
}
