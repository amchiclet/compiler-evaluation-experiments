#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern signed int neuron;
extern int NNTOT;
extern signed int * __restrict__ tempvecC;
typedef float real;
extern real * __restrict__ tempvecA;

void loop()
{
  int __neuron_0__ = neuron;
  
#pragma scop
{
    for (__neuron_0__ = 0; __neuron_0__ <= NNTOT - 1; __neuron_0__ += 1) {
      tempvecC[__neuron_0__] = (tempvecA[__neuron_0__] > 0?1 : - 1);
    }
  }
  
#pragma endscop
  neuron = __neuron_0__;
}
