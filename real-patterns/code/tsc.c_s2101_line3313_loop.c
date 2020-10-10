#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;
extern float  cc[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        aa[i][i] += bb[i][i] * cc[i][i];
    }

#pragma endscop
}
