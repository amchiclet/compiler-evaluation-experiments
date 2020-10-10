#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double * restrict vector;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) vector[i + 0 * m] =((double )i);

#pragma endscop
}
