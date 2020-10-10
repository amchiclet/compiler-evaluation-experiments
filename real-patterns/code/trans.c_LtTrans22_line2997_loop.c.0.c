#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt deg;
typedef unsigned short uint16_t;
typedef uint16_t UInt2;
extern UInt2 * __restrict__ ptf;
extern UInt2 * __restrict__ ptg;

void loop()
{
  int __i_0__ = i;
  
#pragma scop
  for (__i_0__ = 0; __i_0__ <= deg - 1; __i_0__ += 1) {
    if (ptf[__i_0__] != ptg[__i_0__]) {
      if (ptf[__i_0__] < ptg[__i_0__]) {
        return ;
      }
       else {
        return ;
      }
    }
     else {
    }
  }
  
#pragma endscop
  i = __i_0__;
}
