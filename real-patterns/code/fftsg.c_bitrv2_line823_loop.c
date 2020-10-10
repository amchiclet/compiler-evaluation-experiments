#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int m;
extern int j;
extern int j1;
extern int * restrict ip;
extern int k1;
extern double xr;
extern double * restrict a;
extern double xi;
extern double yr;
extern double yi;
extern int m2;

void loop()
{
#pragma scop

    for(k = 0; k < m; k++)
    {
        for(j = 0; j < k; j++)
        {
            j1 = 2 * j + ip[k];
            k1 = 2 * k + ip[j];
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += m2;
            k1 += 2 * m2;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += m2;
            k1 -= m2;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += m2;
            k1 += 2 * m2;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
        }
        j1 = 2 * k + m2 + ip[k];
        k1 = j1 + m2;
        xr = a[j1];
        xi = a[j1 + 1];
        yr = a[k1];
        yi = a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
    }

#pragma endscop
}
