#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern double  exps[5] ;
extern double  visibleEnergies[100 * 5] ;
extern int v;
extern double sumOfExps;

void loop()
{
#pragma scop

    for(j = 0; j < 5; j++)
    {
        exps[j] = exp(visibleEnergies[v + j]);
        sumOfExps += exps[j];
    }

#pragma endscop
}
