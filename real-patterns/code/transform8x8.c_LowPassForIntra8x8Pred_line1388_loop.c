#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int * restrict PredPel;
extern int  LoopArray[25] ;

void loop()
{
#pragma scop

    for(i = 0; i < 25; i++) PredPel[i] = LoopArray[i];

#pragma endscop
}
