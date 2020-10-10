#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int * restrict out;
extern int * restrict tab;
extern int  bitinv32[32] ;

void loop()
{
#pragma scop

    for(i = 0; i < 32; i++)
    {
        out[i] = tab[bitinv32[i]];
    }

#pragma endscop
}
