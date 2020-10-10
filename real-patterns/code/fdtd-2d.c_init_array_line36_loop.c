#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int tmax;
extern double  _fict_[500 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < tmax; i++) _fict_[i] =((double )i);

#pragma endscop
}
