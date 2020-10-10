#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHnodes;
extern int * restrict nodekind;
extern int j;
extern double ** restrict M;
extern double ** restrict C;
extern double ** restrict M23;
extern double ** restrict C23;
extern double ** restrict V23;
extern double *** restrict disp;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHnodes; i++)
    {
        nodekind[i] = 0;
        for(j = 0; j < 3; j++)
        {
            M[i][j] = 0.0;
            C[i][j] = 0.0;
            M23[i][j] = 0.0;
            C23[i][j] = 0.0;
            V23[i][j] = 0.0;
            disp[0][i][j] = 0.0;
            disp[1][i][j] = 0.0;
            disp[2][i][j] = 0.0;
        }
    }

#pragma endscop
}
