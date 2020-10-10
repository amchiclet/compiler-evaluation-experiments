#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int j;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  d[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 / 2; i++)
    {
        k = j + 1;
        a[i] = b[k] - d[i];
        j = k + 1;
        b[k] = a[i] + c[k];
    }

#pragma endscop
}
