#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int kk;
extern unsigned long y;
extern unsigned long  mt[624] ;
extern unsigned long  mag01[2] ;

void loop()
{
#pragma scop

    for(kk = 0; kk < 624 - 397; kk++)
    {
        y = mt[kk] & 0x80000000UL | mt[kk + 1] & 0x7fffffffUL;
        mt[kk] = mt[kk + 397] ^ y >> 1 ^ mag01[y & 0x1UL];
    }

#pragma endscop
}
