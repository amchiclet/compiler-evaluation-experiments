#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int v;
typedef short int16_t;
extern int16_t * restrict tab;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        v |= abs(tab[i]);
    }

#pragma endscop
}
