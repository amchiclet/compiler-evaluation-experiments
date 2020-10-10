#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int  indx[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        indx[i] =(i + 1) % 4 + 1;
    }

#pragma endscop
}
