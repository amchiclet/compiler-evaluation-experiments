#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int net;
extern int numnets;
extern int tot_missing_rows;
extern int * restrict missing_rows;
extern int tot_num_feeds;
extern int * restrict num_feeds;

void loop()
{
#pragma scop

    for(net = 1; net <= numnets; net++)
    {
        tot_missing_rows += missing_rows[net];
        tot_num_feeds += num_feeds[net];
    }

#pragma endscop
}
