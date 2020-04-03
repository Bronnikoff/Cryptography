// Made by Bronnikov Max
#ifndef KECCAK_H
#define KECCAK_H

#include <string>
#include <iostream>
#include <vector>
#include <inttypes.h>
#include <exception>

using namespace std;


// you can absorve this by many blocks for many times or compute and return hash for 1 input block
class Keccak1600{
public:
    // standart Keccak[1024](M, 512)
    Keccak1600();
    // Keccak[c](M, 512)
    Keccak1600(uint16_t r, uint16_t c);
    // Keccak[c](M||del, 512)
    Keccak1600(uint16_t r, uint16_t c, uint8_t del);
    // Keccak[c](M||del, osize*8)
    Keccak1600(uint16_t r, uint16_t c, uint8_t del, uint8_t rnds);
    

    void set_delimeter(uint8_t del); // set delimeter for padding
    void set_output_size(uint16_t bytesize);
    void set_nrounds(uint8_t rnds);

    void push_bytes(const uint8_t* bytes, uint32_t bytesize); // absorve blocks of bytes in function

    void get_hash(uint8_t* hash); // get hash function result of current state

    void hash_compute(const uint8_t* input, uint8_t bytesize, uint8_t* output); // if need compute and return hash of 1 block use this

    void string_hash_to_vec(const string& input, vector<uint8_t>& output);
    
private:

    uint64_t a(uint8_t x, uint8_t y);

    uint64_t* A(uint8_t x, uint8_t y);

    uint64_t ROT(uint64_t line, uint8_t num);

    void Keccak_f();
    void Tetta();
    void PiRo();
    void Hi();
    void Li();

    uint64_t RC();
    bool LFSR();

    uint8_t LFSRState;


    const uint8_t lenght = 6;
    const uint16_t bits = 1600;
    uint16_t capacity; // in bytes
    uint16_t rate; // in bytes

    uint8_t delimiter;

    uint8_t state[200]; // 200 * 8 = 1600
    uint16_t readed_bytes;

    uint16_t output_size;

    uint16_t nrounds;
};




#endif