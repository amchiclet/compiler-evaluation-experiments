#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern float  a[32000] ;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int j = 0; j < 32000 / 2; j++)
    {
        for(int i = 0; i < m; i++)
        {
            a[i] += b[i + m - j - 1] * c[j];
        }
    }

#pragma endscop
}
