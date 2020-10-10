#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long n;
extern long i;
extern double norm;
extern double * restrict out;

void loop()
{
#pragma scop

    for(j = 2; j < n - 2; j++) for(i = 2; i < n - 2; i++)
        {
            norm +=((double )((out[i + j * n] >= 0?out[i + j * n] : -out[i + j * n])));
        }

#pragma endscop
}
