#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern signed int neuron;
extern int NNTOT;
typedef float real;
extern real * restrict tempvecA;
extern signed int* restrict dest;
extern signed int* restrict source;

void loop()
{
#pragma scop

    for(neuron = 0; neuron < NNTOT; neuron++) tempvecA[neuron] =(dest[neuron] = source[neuron]);

#pragma endscop
}
