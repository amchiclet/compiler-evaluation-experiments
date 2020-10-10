#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float x;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        x = a[32000 - i - 1] + b[i] * c[i];
        a[i] = x -((float )1.);
        b[i] = x;
    }

#pragma endscop
}
