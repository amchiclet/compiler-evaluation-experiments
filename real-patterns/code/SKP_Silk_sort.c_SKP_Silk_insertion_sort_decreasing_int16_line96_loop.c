#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int K;
extern int * restrict index;

void loop()
{
#pragma scop

    for(i = 0; i < K; i++)
    {
        index[i] = i;
    }

#pragma endscop
}
