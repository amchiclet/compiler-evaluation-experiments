#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long n;
extern long i;
extern double norm_in;
extern double * restrict in;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++) for(i = 0; i < n; i++)
        {
            norm_in +=((double )((in[i + j * n] >= 0?in[i + j * n] : -in[i + j * n])));
        }

#pragma endscop
}
