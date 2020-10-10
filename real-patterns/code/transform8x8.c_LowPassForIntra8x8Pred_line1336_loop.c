#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  LoopArray[25] ;
extern int * restrict PredPel;

void loop()
{
#pragma scop

    for(i = 0; i < 25; i++) LoopArray[i] = PredPel[i];

#pragma endscop
}
