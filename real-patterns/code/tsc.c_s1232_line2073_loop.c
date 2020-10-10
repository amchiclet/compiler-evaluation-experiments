#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float  bb[256][256] ;
extern float  cc[256][256] ;

void loop()
{
#pragma scop

    for(int j = 0; j < 256; j++)
    {
        for(int i = j; i < 256; i++)
        {
            aa[i][j] = bb[i][j] + cc[i][j];
        }
    }

#pragma endscop
}
