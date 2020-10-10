#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int* restrict out;

void loop()
{
#pragma scop

    for(j = n + 1; j > 2; j--)
    {
        out[j] = out[j - 1];
    }

#pragma endscop
}
