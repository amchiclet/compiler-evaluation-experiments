#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int n;
extern double x;
extern double a;
extern double * restrict window;
extern int j;
extern int iter;

void loop()
{
#pragma scop

    for(k = 0; k < n; k++)
    {
        x =(k *(n - k)) * a;
        window[k] = 1.0;
        for(j = iter; j > 0; j--)
        {
            window[k] = window[k] * x /(j * j) + 1.0;
        }
    }

#pragma endscop
}
