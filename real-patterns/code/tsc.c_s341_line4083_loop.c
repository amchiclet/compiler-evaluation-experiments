#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  b[32000] ;
extern int j;
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        if(b[i] >((float )0.))
        {
            j++;
            a[j] = b[i];
        }
    }

#pragma endscop
}
