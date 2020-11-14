#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict c;
extern int j;
extern double angle;
extern double pi;
extern double * restrict fx;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        c[i] = 0.0;
        for(j = 0; j < n; j++)
        {
            angle =((double )(i *(2 * j + 1))) * pi /((double )(2 * n));
            c[i] = c[i] + fx[j] * cos(angle);
        }
    }

#pragma endscop
}
