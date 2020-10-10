#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  b[32000] ;
extern float * restrict xx;
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 / 2; i++)
    {
        b[i] = xx[i] + a[i];
    }

#pragma endscop
}
