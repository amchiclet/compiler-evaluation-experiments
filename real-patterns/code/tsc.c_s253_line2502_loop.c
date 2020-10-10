#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float s;
extern float  d[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(a[i] > b[i])
        {
            s = a[i] - b[i] * d[i];
            c[i] += s;
            a[i] = s;
        }
    }

#pragma endscop
}
