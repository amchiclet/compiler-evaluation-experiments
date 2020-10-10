#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w_size;
extern double * restrict Hs;
extern double * restrict s;

void loop()
{
#pragma scop

    for(i = 0; i < w_size; i++) Hs[i] = s[i] + 2 * Hs[i];

#pragma endscop
}
