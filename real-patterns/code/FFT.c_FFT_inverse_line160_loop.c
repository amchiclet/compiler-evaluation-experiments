#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int N;
extern double * restrict data;
extern double norm;

void loop()
{
#pragma scop

    for(i = 0; i < N; i++) data[i] *= norm;

#pragma endscop
}
