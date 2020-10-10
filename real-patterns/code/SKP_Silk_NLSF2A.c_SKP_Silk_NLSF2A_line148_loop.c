#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int d;
extern short * restrict a;
extern int  a_int32[16] ;

void loop()
{
#pragma scop

    for(k = 0; k < d; k++)
    {
        a[k] =((short )a_int32[k]);
    }

#pragma endscop
}
