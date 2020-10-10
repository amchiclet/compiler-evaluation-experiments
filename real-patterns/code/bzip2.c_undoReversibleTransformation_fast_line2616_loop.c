#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  cftab[257] ;

void loop()
{
#pragma scop

    for(i = 1; i <= 256; i++) cftab[i] += cftab[i - 1];

#pragma endscop
}
