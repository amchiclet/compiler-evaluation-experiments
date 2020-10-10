#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  cbval[513] ;
extern int  partition[513] ;
extern double * restrict bark;

void loop()
{
#pragma scop

    for(i = 1; i < 513; i++) cbval[partition[i]] += bark[i];

#pragma endscop
}
