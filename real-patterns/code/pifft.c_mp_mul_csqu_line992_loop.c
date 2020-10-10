#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nfft;
extern double xr;
extern double* restrict dinout;
extern double xi;

void loop()
{
#pragma scop

    for(j = 3; j < nfft; j += 2)
    {
        xr = dinout[j];
        xi = dinout[j + 1];
        dinout[j] = xr * xr - xi * xi;
        dinout[j + 1] = 2 * xr * xi;
    }

#pragma endscop
}
