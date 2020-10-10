#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int n;
extern double beta;
extern double alpha;
extern double sum;
extern int i;
extern double  r[2000 + 0] ;
extern double  y[2000 + 0] ;
extern double  z[2000] ;

void loop()
{
#pragma scop

    for(k = 1; k < n; k++)
    {
        beta =(1 - alpha * alpha) * beta;
        sum = 0.0;
        for(i = 0; i < k; i++)
        {
            sum += r[k - i - 1] * y[i];
        }
        alpha = -(r[k] + sum) / beta;
        for(i = 0; i < k; i++)
        {
            z[i] = y[i] + alpha * y[k - i - 1];
        }
        for(i = 0; i < k; i++)
        {
            y[i] = z[i];
        }
        y[k] = alpha;
    }

#pragma endscop
}
