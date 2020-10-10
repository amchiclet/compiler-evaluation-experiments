#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int v;
extern double  edges[100 * 5 + 1][3 * 100 + 1] ;
extern int  pos[500 + 1][300 + 1] ;
extern int  neg[500 + 1][300 + 1] ;

void loop()
{
#pragma scop

    for(v = 0; v < 100 * 5 + 1; v++)
    {
        int h;
        for(h = 0; h < 3 * 100 + 1; h++) edges[v][h] = edges[v][h] + 0.1 *(pos[v][h] - neg[v][h]);
    }

#pragma endscop
}
