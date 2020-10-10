#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double angle;
extern double pi;
extern double * restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        angle =((double )(2 *(n - i) - 1)) * pi /((double )(2 * n));
        x[i] = cos(angle);
    }

#pragma endscop
}
