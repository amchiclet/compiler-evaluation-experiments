#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHnodes;
extern int j;
extern double *** restrict disp;
extern int disptplus;
extern double ** restrict M;
struct excitation
{
    double dt;
    double duration;
    double t0;
};

extern struct excitation Exc;
extern double ** restrict C;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHnodes; i++) for(j = 0; j < 3; j++) disp[disptplus][i][j] = disp[disptplus][i][j] /(M[i][j] + Exc . dt / 2.0 * C[i][j]);

#pragma endscop
}
