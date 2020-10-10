#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float * restrict xx;
extern float * restrict yy;
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 - 1; i++)
    {
        xx[i] = yy[i + 1] + a[i];
    }

#pragma endscop
}
