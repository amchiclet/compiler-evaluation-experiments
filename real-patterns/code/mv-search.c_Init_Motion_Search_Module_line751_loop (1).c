#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int bits;
extern int max_mv_bits;
extern int imax;
extern int imin;
extern int i;
extern int * restrict mvbits;

void loop()
{
#pragma scop

    for(bits = 3; bits <= max_mv_bits; bits += 2)
    {
        imax = 1 <<(bits >> 1);
        imin = imax >> 1;
        for(i = imin; i < imax; i++) mvbits[-i] = mvbits[i] = bits;
    }

#pragma endscop
}
