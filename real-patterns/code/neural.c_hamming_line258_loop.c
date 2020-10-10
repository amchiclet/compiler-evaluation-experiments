#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int neuron;
extern int NNTOT;
extern signed int * restrict ny;
extern signed int * restrict orig;
extern int mode;
extern int hd;

void loop()
{
#pragma scop

    for(neuron = 0; neuron < NNTOT; neuron++) if(ny[neuron] != orig[neuron] * mode) hd++;

#pragma endscop
}
