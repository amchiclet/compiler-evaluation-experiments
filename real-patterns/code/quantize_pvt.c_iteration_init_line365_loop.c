#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef float FLOAT;
extern FLOAT  pow20[256 + 1 + 116 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i <= 256 + 1 + 116; i++) pow20[i] =(pow(2.0,((double )(i - 210 - 116)) * 0.25));

#pragma endscop
}
