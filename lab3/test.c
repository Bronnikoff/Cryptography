#include <stdio.h>
#include <stdint.h>


// this code give information about byte numbering in your computer
// if big-endian, my Keccak realisation will work wrong
int main(void)
{
  uint16_t x = 1; /* 0000 0001 */
  printf("%s\n", *((uint8_t *) &x) == 0 ? "big-endian" : "little-endian");
  return 0;
}
