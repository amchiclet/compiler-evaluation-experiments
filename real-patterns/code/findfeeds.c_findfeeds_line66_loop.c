#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int net;
extern int numnets;
extern int * restrict feed_location;

void loop()
{
#pragma scop

    for(net = 0; net <= numnets; net++)
    {
        feed_location[net] = 0;
    }

#pragma endscop
}
