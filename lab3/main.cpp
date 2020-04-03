// Made by Bronnikov Max
#include <string>
#include <iostream>
#include <vector>
#include "Keccak/Keccak.h"

using namespace std;

// Notation: if you want get SHA-3 use 0x06 delimeter, if classic Keccak1600 use 0x01 


int main(){
    Keccak1600 hasher(72*8, 128*8, 0x06); // Classic SHA-3
    string input = "privetiki men";
    vector<uint8_t> output;
    output.resize(64);
    hasher.string_hash_to_vec(input, output);
    for(uint8_t i = 0; i < 64; ++i){
        cout << hex << int(output[i]) << ' ';
    }
    cout << endl;
    return 0;
}
