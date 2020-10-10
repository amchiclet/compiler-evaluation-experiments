#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  array[256 * 256] ;
extern float * restrict xx;
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 - 1; i++)
    {
        array[i + 1] = xx[i] + a[i];
    }

#pragma endscop
}
