#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern int j;
extern int k;
extern float  b[32000] ;
extern float  c[32000] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 256; i++)
    {
        aa[j][i] = aa[k][i - 1] + b[i] * c[1];
    }

#pragma endscop
}
