#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nwh;
extern double wk1r;
extern double * restrict w;
extern int nw0;
extern double wk1i;
extern double wk3r;
extern double wk3i;
extern int nw1;

void loop()
{
#pragma scop

    for(j = 4; j < nwh; j += 4)
    {
        wk1r = w[nw0 + 2 * j];
        wk1i = w[nw0 + 2 * j + 1];
        wk3r = w[nw0 + 2 * j + 2];
        wk3i = w[nw0 + 2 * j + 3];
        w[nw1 + j] = wk1r;
        w[nw1 + j + 1] = wk1i;
        w[nw1 + j + 2] = wk3r;
        w[nw1 + j + 3] = wk3i;
    }

#pragma endscop
}
