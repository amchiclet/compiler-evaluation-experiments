#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  r[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        r[i] =(n + 1 - i);
    }

#pragma endscop
}
