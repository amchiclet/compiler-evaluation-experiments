#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int m;
extern int k;
extern int n;
extern int kk;
extern int ks;
extern double wkr;
extern double * restrict c;
extern int nc;
extern double wki;
extern double xr;
extern double * restrict a;
extern double xi;
extern double yr;
extern double yi;

void loop()
{
#pragma scop

    for(j = 2; j < m; j += 2)
    {
        k = n - j;
        kk += ks;
        wkr = 0.5 - c[nc - kk];
        wki = c[kk];
        xr = a[j] - a[k];
        xi = a[j + 1] + a[k + 1];
        yr = wkr * xr - wki * xi;
        yi = wkr * xi + wki * xr;
        a[j] -= yr;
        a[j + 1] -= yi;
        a[k] += yr;
        a[k + 1] -= yi;
    }

#pragma endscop
}
