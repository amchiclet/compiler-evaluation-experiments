#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int order;
extern int energy;
extern short * restrict x;
extern int rshifts_local;

void loop()
{
#pragma scop

    for(i = 0; i < order - 1; i++)
    {
        energy -=((int )((short )x[i])) *((int )((short )x[i])) >> rshifts_local;
    }

#pragma endscop
}
