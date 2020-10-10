#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int numf1s;
extern int j;
extern int start;
extern int numf2s;
extern double ** restrict bus;
extern double d;

void loop()
{
#pragma scop

    for(i = 0; i < numf1s; i++) for(j = start; j < numf2s; j++) bus[i][j] = 1 /(1.0 - d) / sqrt(((double )numf1s));

#pragma endscop
}
