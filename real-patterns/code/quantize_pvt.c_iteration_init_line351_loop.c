#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef float FLOAT;
extern FLOAT  pow43[8206 + 2] ;

void loop()
{
#pragma scop

    for(i = 1; i < 8206 + 2; i++) pow43[i] =(pow(((FLOAT )i),4.0 / 3.0));

#pragma endscop
}
