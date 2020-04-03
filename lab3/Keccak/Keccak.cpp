// Made by Bronnikov Max
#include "Keccak.h"
#include <cstring>

Keccak1600::Keccak1600(){
    delimiter = 0x01;
    output_size = 64;
    rate = 72;
    capacity = 128;
    nrounds = 24;
    readed_bytes = 0;
    memset(state, 0, 200 * sizeof(uint8_t));
}

Keccak1600::Keccak1600(uint16_t r, uint16_t c, uint8_t del){
    if(r & 7){
        throw exception();
    }
    if(c & 7){
        throw exception();
    }
    rate = r >> 3;
    capacity = c >> 3;
    delimiter = del;
    output_size = 64;
    nrounds = 24;
    readed_bytes = 0;
    if(((rate + capacity) << 3) != bits){
        throw exception();
    }
    memset(state, 0, 200 * sizeof(uint8_t));
}

Keccak1600::Keccak1600(uint16_t r, uint16_t c){
    if(r & 7){
        throw exception();
    }
    if(c & 7){
        throw exception();
    }
    rate = r >> 3;
    capacity = c >> 3;
    delimiter = 0x01;
    output_size = 64;
    nrounds = 24;
    readed_bytes = 0;
    if(((rate + capacity) << 3) != bits){
        throw exception();
    }
    memset(state, 0, 200 * sizeof(uint8_t));
}

Keccak1600::Keccak1600(uint16_t r, uint16_t c, uint8_t del, uint8_t rnds){
    if(r & 7){
        throw exception();
    }
    if(c & 7){
        throw exception();
    }
    rate = r >> 3;
    capacity = c >> 3;
    delimiter = del;
    output_size = 64;
    nrounds = rnds;
    readed_bytes = 0;
    if(((rate + capacity) << 3) != bits){
        throw exception();
    }
    memset(state, 0, 200 * sizeof(uint8_t));
}

void Keccak1600::set_delimeter(uint8_t del){
    delimiter = del;
}

void Keccak1600::set_nrounds(uint8_t rnds){
    nrounds = rnds;
}


void Keccak1600::set_output_size(uint16_t bytesize){
    if(bytesize < 1){
        throw exception();
    }
    output_size = bytesize;
}


uint64_t Keccak1600::a(uint8_t x, uint8_t y){
    return *((uint64_t*)&state[sizeof(uint64_t)*(5*y + x)]);
}


uint64_t* Keccak1600::A(uint8_t x, uint8_t y){
    return (uint64_t*)&state[sizeof(uint64_t)*(5*y + x)];
}


uint64_t Keccak1600::ROT(uint64_t line, uint8_t num){
    return (line << num) ^ (line >> (64 - num));
}


bool Keccak1600::LFSR(){
    if(LFSRState & 0x80){
        LFSRState <<= 1;
        LFSRState ^= 0x71;
        return true;
    }
    LFSRState <<= 1;
    return false;
}


uint64_t Keccak1600::RC(){
    uint64_t constant = 0;
    for(uint8_t j = 0; j <= lenght; ++j){
        if(LFSR()){
            constant |= (uint64_t)1 << ((1 << j) - 1);
        }
    }
    return constant;
}


void Keccak1600::Tetta(){
    uint64_t C[5];
    for(uint8_t x = 0; x < 5; ++x){
        C[x] = a(x, 0);
        for(uint8_t y = 1; y < 5; ++y){
            C[x] ^= a(x, y);
        }
    }
    for(uint8_t x = 0; x < 5; ++x){
        uint64_t D = C[x - 1 >= 0 ? x - 1 : 4];
        D ^= ROT(C[x + 1 < 5 ? x + 1 : 0], 1);
        for(uint8_t y = 0; y < 5; ++y){
            *A(x, y) = a(x, y) ^ D;
        }
    }
}

void Keccak1600::PiRo(){
    uint8_t x = 1, y = 0;
    uint64_t line = a(x, y);
    for(uint16_t t = 0; t < 24; ++t){
        uint8_t Y = ((x << 1) + 3 * y) % 5;
        x = y;
        y = Y;
        uint64_t newline = a(x, y);
        *A(x, y) = ROT(line, ((t + 1)*(t + 2) >> 1) % 64);
        line = newline;
    }
}


void Keccak1600::Hi(){
    for(uint8_t y = 0; y < 5; ++y){
        uint64_t C[5];
        for(uint8_t x = 0; x < 5; ++x){
            C[x] = a(x, y);
        }

        for(uint8_t x = 0; x < 5; ++x){
            *A(x, y) = C[x] ^ (~C[x + 1 < 5 ? x + 1 : x - 4] & C[x + 2 < 5 ? x + 2 : x - 3]);
        }
    }
}


void Keccak1600::Li(){
    *A(0, 0) ^= RC();
}


void Keccak1600::Keccak_f(){
    LFSRState = 0xB8;
    for(uint8_t i = 0; i < nrounds; ++i){
        Tetta();
        PiRo();
        Hi();
        Li();
    }
}



void Keccak1600::push_bytes(const uint8_t* bytes, uint32_t bytesize){
    for(uint32_t i = 0; i < bytesize; ++i){
        state[readed_bytes++] ^= bytes[i];
        if(readed_bytes == rate){
            Keccak_f();
            readed_bytes = 0;
        }
    }
}


void Keccak1600::get_hash(uint8_t* hash){
    state[readed_bytes++] ^= delimiter;
    if(readed_bytes == rate && (delimiter & 0x80)){
        Keccak_f();
    }
    state[rate - 1] ^= 0x80;
    readed_bytes = 0;
    Keccak_f();

    uint16_t in_rate = 0;
    for(uint16_t i = 0; i < output_size; ++i){
        hash[i] = state[in_rate++];
        if(in_rate == rate){
            Keccak_f();
            in_rate = 0;
        }
    }   
}


void Keccak1600::hash_compute(const uint8_t* input, uint8_t bytesize, uint8_t* output){
    memset(state, 0, 200 * sizeof(uint8_t));
    readed_bytes = 0;
    push_bytes(input, bytesize);
    get_hash(output);
}

void Keccak1600::string_hash_to_vec(const string& input, vector<uint8_t>& output){
    output.resize(output_size);
    hash_compute((const uint8_t*)input.c_str(), input.size(), output.data());
}

