#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long n;
extern long i;
extern double * restrict in;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++) for(i = 0; i < n; i++) in[i + j * n] +=((double )1.0);

#pragma endscop
}
