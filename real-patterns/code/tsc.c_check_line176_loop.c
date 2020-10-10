#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float sumaa;
extern float  aa[256][256] ;
extern float sumbb;
extern float  bb[256][256] ;
extern float sumcc;
extern float  cc[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            sumaa += aa[i][j];
            sumbb += bb[i][j];
            sumcc += cc[i][j];
        }
    }

#pragma endscop
}
