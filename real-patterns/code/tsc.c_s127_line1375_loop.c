#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;
extern float  e[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 / 2; i++)
    {
        j++;
        a[j] = b[i] + c[i] * d[i];
        j++;
        a[j] = b[i] + d[i] * e[i];
    }

#pragma endscop
}
