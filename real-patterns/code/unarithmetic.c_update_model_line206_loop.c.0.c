#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int freq[256 + 1 + 1];
extern int cum_freq[256 + 1 + 1];
extern int cum;

void loop()
{
  int __i_0__ = i;
  
#pragma scop
  for (__i_0__ = 256 + 1; __i_0__ >= 0; __i_0__ += - 1) {
    freq[__i_0__] = (freq[__i_0__] + 1) / 2;
    cum_freq[__i_0__] = cum;
    cum += freq[__i_0__];
  }
  
#pragma endscop
  i = __i_0__;
}
