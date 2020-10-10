#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 2; i < 32000; i++)
    {
        a[i] = a[i] + a[i - 1] * b[i] + a[i - 2] * c[i];
    }

#pragma endscop
}
