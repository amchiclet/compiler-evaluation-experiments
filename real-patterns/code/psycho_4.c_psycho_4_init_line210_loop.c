#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict window;

void loop()
{
#pragma scop

    for(i = 0; i < 1024; i++) window[i] = 0.5 *(1 - cos(2.0 * 3.14159265358979 *(i - 0.5) / 1024));

#pragma endscop
}
