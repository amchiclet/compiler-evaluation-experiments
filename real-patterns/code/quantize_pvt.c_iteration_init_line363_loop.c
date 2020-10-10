#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef float FLOAT;
extern FLOAT  ipow20[256 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i < 256 + 1; i++) ipow20[i] =(pow(2.0,((double )(i - 210)) * - 0.1875));

#pragma endscop
}
