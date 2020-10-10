#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict w;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) w[i] = 0;

#pragma endscop
}
