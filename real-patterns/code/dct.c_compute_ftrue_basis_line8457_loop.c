#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int i;
extern double  basis[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++)
    {
        for(i = 0; i < n; i++)
        {
            basis[j][i] = sqrt(2.0 / n) * cos((i + 0.5) * j * 3.14159265358979323846 / n);
            if(j == 0) basis[j][i] *= 0.70710678118654752440;
        }
    }

#pragma endscop
}
