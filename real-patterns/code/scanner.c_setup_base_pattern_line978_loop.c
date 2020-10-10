#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int numf1s;
extern int j;
extern int spot;
extern int numf2s;
extern double ** restrict tds;
extern double ** restrict bus;
extern double d;

void loop()
{
#pragma scop

    for(i = 0; i < numf1s; i++)
    {
        for(j = spot; j < numf2s; j++)
        {
            tds[i][j] = bus[i][j] = 1.0 / sqrt(((double )numf1s)) /(1 - d);
        }
    }

#pragma endscop
}
