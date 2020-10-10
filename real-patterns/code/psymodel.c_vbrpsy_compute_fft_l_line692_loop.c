#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
typedef float FLOAT;
extern FLOAT totalenergy;
extern FLOAT  fftenergy[1024 / 2 + 1] ;

void loop()
{
#pragma scop

    for(j = 11; j < 1024 / 2 + 1; j++) totalenergy += fftenergy[j];

#pragma endscop
}
