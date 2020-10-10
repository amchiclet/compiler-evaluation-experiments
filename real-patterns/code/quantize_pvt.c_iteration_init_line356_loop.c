#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef float FLOAT;
extern FLOAT  adj43asm[8206 + 2] ;
extern FLOAT  pow43[8206 + 2] ;

void loop()
{
#pragma scop

    for(i = 1; i < 8206 + 2; i++) adj43asm[i] =(i - 0.5 - pow(0.5 *(pow43[i - 1] + pow43[i]),0.75));

#pragma endscop
}
