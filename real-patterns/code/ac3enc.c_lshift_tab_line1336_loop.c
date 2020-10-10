#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef short int16_t;
extern int16_t * restrict tab;
extern int lshift;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        tab[i] <<= lshift;
    }

#pragma endscop
}
