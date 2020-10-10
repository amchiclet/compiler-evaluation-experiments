#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  bb[256][256] ;
extern int k;
extern float  array[256 * 256] ;
extern float  aa[256][256] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            if(bb[j][i] >((float )0.))
            {
                k++;
                array[k] = aa[j][i];
            }
        }
    }

#pragma endscop
}
