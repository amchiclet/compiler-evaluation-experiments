#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  aa[256][256] ;
extern float max;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            if(aa[i][j] > max)
            {
                max = aa[i][j];
            }
        }
    }

#pragma endscop
}
