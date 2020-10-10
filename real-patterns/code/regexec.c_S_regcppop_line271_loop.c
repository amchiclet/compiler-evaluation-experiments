#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int U32;
extern U32 paren;
extern U32 * restrict PL_reglastparen;
typedef int I32;
extern I32 PL_regnpar;
extern I32 PL_regsize;
extern I32 * restrict PL_regstartp;
extern I32 * restrict PL_regendp;

void loop()
{
#pragma scop

    for(paren = *PL_reglastparen + 1; ((I32 )paren) <= PL_regnpar; paren++)
    {
        if(((I32 )paren) > PL_regsize) PL_regstartp[paren] = - 1;
        PL_regendp[paren] = - 1;
    }

#pragma endscop
}
