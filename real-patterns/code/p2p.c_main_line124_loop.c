#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int i;
extern int m;
extern double * restrict vector;

void loop()
{
#pragma scop

    for(j = 1; j < n; j++) for(i = 1; i < m; i++)
        {
            vector[i + j * m] = vector[i - 1 + j * m] + vector[i +(j - 1) * m] - vector[i - 1 +(j - 1) * m];
        }

#pragma endscop
}
