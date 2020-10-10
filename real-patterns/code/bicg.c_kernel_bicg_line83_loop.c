#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double  s[1900 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) s[i] = 0;

#pragma endscop
}
