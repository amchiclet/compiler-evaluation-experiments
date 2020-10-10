#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict s;
extern double * restrict r;
extern double * restrict g;
extern double * restrict d;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        s[i] = 0;
        r[i] = -g[i];
        d[i] = r[i];
    }

#pragma endscop
}
