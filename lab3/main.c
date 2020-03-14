#include <stdio.h>
#include <string.h>
#include "keccakteam.h"

int def(char* input){
    input[0] = 'l';
    printf("def: %s\n", input);
    return 1;
}

int main(){
    char input[14] = "privetiki men";
    char output[65];
    output[64] = '\0';
    FIPS202_SHA3_512(input, 13, output);
    printf("input: %s\n", input);
    printf("output: ");
    for(int i = 0; i < 64; ++i){
        printf("0x%X ", (UINT8)output[i]);
    }
    putchar('\n');
    return 0;
}