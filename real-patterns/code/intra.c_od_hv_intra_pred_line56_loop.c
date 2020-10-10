#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict pred;
extern od_coeff * restrict t;
extern int n;
extern int w;

void loop()
{
#pragma scop

    for(i = 1; i < 4; i++) pred[i] = t[-n * w + i];

#pragma endscop
}
