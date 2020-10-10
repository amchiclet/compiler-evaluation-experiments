#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int numf1s;
extern int j;
extern int start;
extern int numf2s;
extern double ** restrict tds;

void loop()
{
#pragma scop

    for(i = 0; i < numf1s; i++) for(j = start; j < numf2s; j++) tds[i][j] = 0.0;

#pragma endscop
}
