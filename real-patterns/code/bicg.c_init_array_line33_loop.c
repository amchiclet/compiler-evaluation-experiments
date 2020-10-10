#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double  p[1900 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) p[i] =((double )(i % m)) / m;

#pragma endscop
}
