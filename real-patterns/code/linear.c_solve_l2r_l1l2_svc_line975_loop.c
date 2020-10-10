#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w_size;
extern double * restrict w;

void loop()
{
#pragma scop

    for(i = 0; i < w_size; i++) w[i] = 0;

#pragma endscop
}
