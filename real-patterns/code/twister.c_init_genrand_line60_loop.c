#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int mti;
extern unsigned long  mt[624] ;

void loop()
{
#pragma scop

    for(mti = 1; mti < 624; mti++)
    {
        mt[mti] = 1812433253UL *(mt[mti - 1] ^ mt[mti - 1] >> 30) + mti;
        mt[mti] &= 0xffffffffUL;
    }

#pragma endscop
}
