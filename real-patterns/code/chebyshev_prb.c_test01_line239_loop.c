#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict x;
extern double a;
extern double b;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        x[i] = 0.5 *(a + b) + x[i] * 0.5 *(b - a);
    }

#pragma endscop
}
