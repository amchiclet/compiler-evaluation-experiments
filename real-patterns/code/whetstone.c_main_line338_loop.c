#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern long I;
extern long N11;
extern double X;
extern double T1;

void loop()
{
#pragma scop

    for(I = 1; I <= N11; I++) X = sqrt((exp(log(X) / T1)));

#pragma endscop
}
