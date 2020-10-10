#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double ** restrict xx;

void loop()
{
#pragma scop

    for(i = 1; i < 1 << 28 - 16; i++) xx[i] = xx[i - 1] + 2 *(1 << 16);

#pragma endscop
}
