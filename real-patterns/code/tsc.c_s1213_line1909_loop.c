#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 32000 - 1; i++)
    {
        a[i] = b[i - 1] + c[i];
        b[i] = a[i + 1] * d[i];
    }

#pragma endscop
}
