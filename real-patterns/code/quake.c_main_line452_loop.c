#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHnodes;
extern int j;
extern double *** restrict disp;
extern int disptplus;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHnodes; i++) for(j = 0; j < 3; j++) disp[disptplus][i][j] = 0.0;

#pragma endscop
}
