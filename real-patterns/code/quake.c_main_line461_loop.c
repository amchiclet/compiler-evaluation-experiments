#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHnodes;
extern int j;
extern double *** restrict disp;
extern int disptplus;
struct excitation
{
    double dt;
    double duration;
    double t0;
};

extern struct excitation Exc;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHnodes; i++) for(j = 0; j < 3; j++) disp[disptplus][i][j] *= -Exc . dt * Exc . dt;

#pragma endscop
}
