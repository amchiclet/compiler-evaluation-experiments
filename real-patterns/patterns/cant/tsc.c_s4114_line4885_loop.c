#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n1;
extern int k;
extern int * restrict ip;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;
extern float  d[32000] ;

void loop()
{
#pragma scop

    for(int i = n1 - 1; i < 32000; i++)
    {
        k = ip[i];
        a[i] = b[i] + c[32000 - k + 1 - 2] * d[i];
        k += 5;
    }

#pragma endscop
}
