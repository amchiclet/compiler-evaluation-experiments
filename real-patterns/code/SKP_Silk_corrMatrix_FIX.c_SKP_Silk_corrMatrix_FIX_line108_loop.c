#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int order;
extern int energy;
extern short * restrict ptr1;
extern int L;
extern int rshifts_local;
extern int * restrict XX;

void loop()
{
#pragma scop

    for(j = 1; j < order; j++)
    {
        energy = energy -(((int )((short )ptr1[L - j])) *((int )((short )ptr1[L - j])) >> rshifts_local);
        energy = energy +(((int )((short )ptr1[-j])) *((int )((short )ptr1[-j])) >> rshifts_local);
        *(XX +(j * order + j)) = energy;
    }

#pragma endscop
}
