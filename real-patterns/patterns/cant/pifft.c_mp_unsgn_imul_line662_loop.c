#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int shift;
extern int* restrict out;

void loop()
{
#pragma scop

    for(j = n; j >= shift + 1; j--)
    {
        out[j] = out[j - shift];
    }

#pragma endscop
}
