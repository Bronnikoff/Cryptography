// Made by Bronnikov Max

// compile: g++ -std=c++11 -Wall -pedantic Keccak/Keccak.cpp diff_analysis.cpp -o run
// run: ./run

#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

#include "Keccak/Keccak.h"

using namespace std;

const char filename[] = "analis.stat";
const int round_limit = 24;
const int tests_number = 100;
const int max_len = 70;
const bool log = false;

// Note: if need SHA-3 - use 0x06 delimeter, if classic Keccak1600 - use 0x01, if some exotik - whatever you want

void string_xor_1(string& ans){
    ans.back() ^= 0x80;
}

void random_strings(string& text1, string& text2){
    unsigned rand_len = 1 + rand() % max_len;
    text1.resize(rand_len);
    for(unsigned i = 0; i < rand_len; ++i){
        if(log){
            text1[i] = 'a' + rand() % 26;
            continue;
        }
        text1[i] = (char)(rand() % 256);
    }
    text2 = text1;
    string_xor_1(text2);
}

int count_diff(const vector<uint8_t>& y1, const vector<uint8_t>& y2){
    int diff = 0;
    for(unsigned i = 0; i < y1.size(); ++i){
        for(uint8_t j = 0; j < 8; ++j){
            diff += ((y1[i] >> j) & (uint8_t)1) ^ ((y2[i] >> j) & (uint8_t)1);
        }
    }
    return diff;
}

void gen_stat(ofstream& output){
    vector<int> diffs(round_limit, 0);
    for(int i = 0; i < tests_number; ++i){
        string X1, X2;
        random_strings(X1, X2);
        if(log){
            cout << endl;
            cout << "Random string:" << endl;
            cout << X1 << endl;
        }
        for(int j = 0; j < round_limit; ++j){
            Keccak1600 hasher(72*8, 128*8, 0x01, j + 1); // Classic Keccak-1600
            vector<uint8_t> Y1, Y2;
            hasher.string_hash_to_vec(X1, Y1);
            hasher.string_hash_to_vec(X2, Y2);
            diffs[j] += count_diff(Y1, Y2);
            if(log){
                cout << "For round number: " << j + 1 << " bits differ count: " << count_diff(Y1, Y2) << endl;
            }
        }
    }

    for(int j = 0; j < round_limit; ++j){
        output << j + 1 << ' ' << (diffs[j] / tests_number) << endl;
        if(log){
            cout << endl;
            cout << "Middle value of diffrent bits for " << j + 1 << " rounds: " << (diffs[j] / tests_number) << endl;
        }
    }
}


int main(){
    srand(time(0));
    ofstream output(filename);
    cout << "Differential analysis counter started!" << endl;
    cout << endl;
    cout << "Number of test strings: " << tests_number << endl;
    cout << "Will explore round numbers from 1 to " << round_limit << endl;
    cout << "Stat will write in file: " << filename << endl;
    gen_stat(output);
    output.close();
    cout << endl;
    cout << "Program made by Max Bronnikov" << endl;
    return 0;
}
