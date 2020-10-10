#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double* restrict res;
extern double* restrict mat1;
extern double* restrict mat2;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++) res[i] = mat1[i] - mat2[i];

#pragma endscop
}
