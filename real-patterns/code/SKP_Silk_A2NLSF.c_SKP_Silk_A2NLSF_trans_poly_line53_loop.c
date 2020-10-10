#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int dd;
extern int n;
extern int * restrict p;

void loop()
{
#pragma scop

    for(k = 2; k <= dd; k++)
    {
        for(n = dd; n > k; n--)
        {
            p[n - 2] -= p[n];
        }
        p[k - 2] -= p[k] << 1;
    }

#pragma endscop
}
