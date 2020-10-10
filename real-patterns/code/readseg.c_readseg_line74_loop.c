#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int net;
extern int numnets;
extern int * restrict anet;

void loop()
{
#pragma scop

    for(net = 0; net <= numnets + 1; net++)
    {
        anet[net] = 0;
    }

#pragma endscop
}
