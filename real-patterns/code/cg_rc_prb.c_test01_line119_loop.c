#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double angle;
extern double pi;
extern double * restrict x_exact;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        angle = 2.0 * pi *((double )i) /((double )(n - 1));
        x_exact[i] = sin(angle);
    }

#pragma endscop
}
