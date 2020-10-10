#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef float FLOAT;
extern FLOAT  window[1024] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1024; i++) window[i] =(0.42 - .5 * cos(2 * 3.14159265358979323846 *(i + .5) / 1024) + 0.08 * cos(4 * 3.14159265358979323846 *(i + .5) / 1024));

#pragma endscop
}
