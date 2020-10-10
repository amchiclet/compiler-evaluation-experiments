#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 32000 - 1; i >= 0; i--)
    {
        a[i] = b[i] +((float )1.);
    }

#pragma endscop
}
