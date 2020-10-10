#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int k;
extern int * restrict seed;
extern int i4_huge;
extern double * restrict r;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        k = *seed / 127773;
        *seed = 16807 *( *seed - k * 127773) - k * 2836;
        if( *seed < 0)
        {
            *seed = *seed + i4_huge;
        }
        r[i] =((double )( *seed)) * 4.656612875E-10;
    }

#pragma endscop
}
