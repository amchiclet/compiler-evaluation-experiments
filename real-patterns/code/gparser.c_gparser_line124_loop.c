#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int numnets;
extern int * restrict top_row_for_this_net;
extern int * restrict bot_row_for_this_net;

void loop()
{
#pragma scop

    for(i = 1; i <= numnets; i++)
    {
        top_row_for_this_net[i] = - 1;
        bot_row_for_this_net[i] = 10000000;
    }

#pragma endscop
}
