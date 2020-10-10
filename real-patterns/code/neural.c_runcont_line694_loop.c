#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern signed int neuron;
extern int NNTOT;
typedef float real;
extern real thesum;
extern real ** restrict Tmatrix;
extern signed int row;
extern signed int* restrict source;

void loop()
{
#pragma scop

    for(neuron = 0; neuron < NNTOT; neuron++) thesum += Tmatrix[row][neuron] * source[neuron];

#pragma endscop
}
