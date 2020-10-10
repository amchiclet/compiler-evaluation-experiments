#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern signed int neuron;
extern int NNTOT;
typedef float real;
extern real * restrict tempvecA;
extern signed int* restrict dest;

void loop()
{
#pragma scop

    for(neuron = 0; neuron < NNTOT; neuron++) tempvecA[neuron] = dest[neuron];

#pragma endscop
}
