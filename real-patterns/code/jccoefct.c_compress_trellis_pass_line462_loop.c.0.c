#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int JDIMENSION;
extern JDIMENSION MCUindex;
extern JDIMENSION MCUs_across;
typedef short JCOEF;
extern JCOEF lastDC;
typedef JCOEF JBLOCK[64];
typedef JBLOCK *JBLOCKROW;
extern  __restrict__ JBLOCKROW lastblockrow;
extern int h_samp_factor;
extern int bi;
extern  __restrict__ JBLOCKROW thisblockrow;

void loop()
{
  int __MCUindex_0__ = MCUindex;
  int __bi_1__ = bi;
  
#pragma scop
{
    for (__MCUindex_0__ = 0; __MCUindex_0__ <= MCUs_across - 1; __MCUindex_0__ += 1) {
      lastDC = lastblockrow[h_samp_factor - 1][0];
      for (__bi_1__ = 0; __bi_1__ <= h_samp_factor - 1; __bi_1__ += 1) {
        thisblockrow[__bi_1__][0] = lastDC;
      }
      thisblockrow += h_samp_factor;
      lastblockrow += h_samp_factor;
    }
  }
  
#pragma endscop
  MCUindex = __MCUindex_0__;
  bi = __bi_1__;
}
