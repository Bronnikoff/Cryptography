#ifndef KECCAK_H
#define KECCAK_H

#include <string>
#include <iostream>
#include <vector>
#include <inttypes.h>

using namespace std;

class Keccak{
public:
    Keccak();
    
private:
    uint8_t delimiter;
    vector<uint8_t> state;
};




#endif