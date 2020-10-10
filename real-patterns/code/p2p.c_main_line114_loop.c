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

    for(j = 0; j < n; j++) for(i = 0; i < m; i++) vector[i + j * m] = 0.0;

#pragma endscop
}
