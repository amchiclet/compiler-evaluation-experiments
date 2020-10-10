#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int reps;
extern int NUM_ITERATIONS;
extern int r;
extern int M;
extern int * restrict row;
extern int i;
extern double * restrict x;
extern int * restrict col;
extern double * restrict val;
extern double * restrict y;

void loop()
{
#pragma scop

    for(reps = 0; reps < NUM_ITERATIONS; reps++)
    {
        for(r = 0; r < M; r++)
        {
            double sum = 0.0;
            int rowR = row[r];
            int rowRp1 = row[r + 1];
            for(i = rowR; i < rowRp1; i++) sum += x[col[i]] * val[i];
            y[r] = sum;
        }
    }

#pragma endscop
}
