#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int i;
extern double* restrict a;
extern int k;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++)
    {
        for(i = 0; i < n; i++)
        {
            if(i == j)
            {
                a[k] = 1.0;
            }
            else
            {
                a[k] = 0.0;
            }
            k = k + 1;
        }
    }

#pragma endscop
}
