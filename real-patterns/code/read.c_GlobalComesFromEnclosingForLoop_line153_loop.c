#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long uint64_t;
typedef uint64_t UInt8;
typedef UInt8 UInt;
extern UInt i;
extern UInt CurrentGlobalForLoopDepth;
extern UInt  CurrentGlobalForLoopVariables[100] ;
extern UInt var;

void loop()
{
#pragma scop

    for(i = 0; i < CurrentGlobalForLoopDepth; i++)
    {
        if(i == 100) return 0;
        if(CurrentGlobalForLoopVariables[i] == var) return 1;
    }

#pragma endscop
}
