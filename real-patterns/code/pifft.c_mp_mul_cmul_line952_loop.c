#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nfft;
extern double xr;
extern double* restrict din;
extern double xi;
extern double yr;
extern double* restrict dinout;
extern double yi;

void loop()
{
#pragma scop

    for(j = 3; j < nfft; j += 2)
    {
        xr = din[j];
        xi = din[j + 1];
        yr = dinout[j];
        yi = dinout[j + 1];
        dinout[j] = xr * yr - xi * yi;
        dinout[j + 1] = xr * yi + xi * yr;
    }

#pragma endscop
}
