#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double* restrict v;
extern double  u[12] ;

void loop()
{
#pragma scop

    for(i = 0; i < 12; i++) v[i] = u[i];

#pragma endscop
}
