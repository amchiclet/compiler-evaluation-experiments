#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int naa;
extern double* restrict x;
extern double* restrict q;
extern double* restrict z;
extern double* restrict r;
extern double* restrict p;
extern double* restrict w;

void loop()
{
#pragma scop

    for(j = 1; j <= naa + 1; j++)
    {
        double xj = x[j];
        q[j] = 0.0;
        z[j] = 0.0;
        r[j] = xj;
        p[j] = xj;
        w[j] = 0.0;
    }

#pragma endscop
}
