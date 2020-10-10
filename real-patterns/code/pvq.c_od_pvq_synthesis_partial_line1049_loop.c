#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nn;
extern int yy;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict ypulse;

void loop()
{
#pragma scop

    for(i = 0; i < nn; i++) yy += ypulse[i] *((int32_t )ypulse[i]);

#pragma endscop
}
