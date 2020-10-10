#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  x[14000 + 2 + 1] ;

void loop()
{
#pragma scop

    for(i = 1; i <= 14000 + 1; i++)
    {
        x[i] = 1.0;
    }

#pragma endscop
}
