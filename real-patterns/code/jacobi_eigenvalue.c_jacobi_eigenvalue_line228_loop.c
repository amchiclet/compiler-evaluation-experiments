#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int n;
extern int m;
extern int l;
extern double* restrict d;
extern double t;
extern int i;
extern double w;
extern double* restrict v;

void loop()
{
#pragma scop

    for(k = 0; k < n - 1; k++)
    {
        m = k;
        for(l = k + 1; l < n; l++)
        {
            if(d[l] < d[m])
            {
                m = l;
            }
        }
        if(m != k)
        {
            t = d[m];
            d[m] = d[k];
            d[k] = t;
            for(i = 0; i < n; i++)
            {
                w = v[i + m * n];
                v[i + m * n] = v[i + k * n];
                v[i + k * n] = w;
            }
        }
    }

#pragma endscop
}
