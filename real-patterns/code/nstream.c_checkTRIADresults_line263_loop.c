#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long length;
extern double asum;
extern double * restrict a;

void loop()
{
#pragma scop

    for(j = 0; j < length; j++) asum += a[j];

#pragma endscop
}
