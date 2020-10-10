#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float x;
extern int index;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; ++i)
    {
        if(a[i] > x)
        {
            x = a[i];
            index = i;
        }
    }

#pragma endscop
}
