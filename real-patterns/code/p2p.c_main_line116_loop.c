#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern double * restrict vector;
extern int m;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++) vector[0 + j * m] =((double )j);

#pragma endscop
}
