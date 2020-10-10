#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int D;
extern int tmp;
extern int * restrict wXx;
extern int  cn[16] ;

void loop()
{
#pragma scop

    for(i = 0; i < D; i++)
    {
        tmp = tmp +((wXx[i] >> 16) *((int )((short )cn[i])) +((wXx[i] & 0x0000FFFF) *((int )((short )cn[i])) >> 16));
    }

#pragma endscop
}
