#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int order;
extern int i;
extern double * restrict A;
extern double * restrict B;
extern double * restrict C;

void loop()
{
#pragma scop

    for(j = 0; j < order; j++) for(i = 0; i < order; i++)
        {
            A[i + order * j] = B[i + order * j] =((double )j);
            C[i + order * j] = 0.0;
        }

#pragma endscop
}
