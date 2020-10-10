#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int maxterm;
extern int * restrict pinlist;

void loop()
{
#pragma scop

    for(i = 1; i <= maxterm; i++)
    {
        pinlist[i] = 0;
    }

#pragma endscop
}
