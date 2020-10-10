#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern int i;
extern int w;
extern unsigned char * __restrict__ d;
extern unsigned char * __restrict__ s;
extern int lx;

void loop()
{
  int __j_0__ = j;
  int __i_1__ = i;
  
#pragma scop
{
    for (__j_0__ = 0; __j_0__ <= h - 1; __j_0__ += 1) {
      for (__i_1__ = 0; __i_1__ <= w - 1; __i_1__ += 1) {
        d[__i_1__] = (d[__i_1__] + (((unsigned int )(s[__i_1__] + s[__i_1__ + 1] + s[__i_1__ + lx] + s[__i_1__ + lx + 1] + 2)) >> 2) + 1 >> 1);
      }
      s += lx;
      d += lx;
    }
  }
  
#pragma endscop
  j = __j_0__;
  i = __i_1__;
}
