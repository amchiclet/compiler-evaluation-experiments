#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int alphaSize;
extern int * restrict base;
extern unsigned char * restrict length;

void loop()
{
#pragma scop

    for(i = 0; i < alphaSize; i++) base[length[i] + 1]++;

#pragma endscop
}
