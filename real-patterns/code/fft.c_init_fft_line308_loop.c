#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef float FLOAT;
extern FLOAT  window_s[256 / 2] ;

void loop()
{
#pragma scop

    for(i = 0; i < 256 / 2; i++) window_s[i] =(.5 *(1.0 - cos(2.0 * 3.14159265358979323846 *(i + .5) / 256)));

#pragma endscop
}
