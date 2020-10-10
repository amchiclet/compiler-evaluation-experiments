#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHelems;
extern int * restrict source_elms;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHelems; i++)
    {
        source_elms[i] = 1;
    }

#pragma endscop
}
