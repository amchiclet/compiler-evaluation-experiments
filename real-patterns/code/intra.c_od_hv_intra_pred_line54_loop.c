#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict pred;
extern od_coeff * restrict t;
extern int w;

void loop()
{
#pragma scop

    for(i = 4; i < n; i++) pred[i * n] = t[-n + i * w];

#pragma endscop
}
