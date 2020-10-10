#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern int iSize;
extern int jj;
extern int maxCol;
extern double ** restrict differentials;

void loop()
{
#pragma scop

    for(ii = 0; ii < iSize; ++ii)
    {
        for(jj = 0; jj < maxCol; ++jj)
        {
            differentials[ii][jj] = 0.0;
        }
    }

#pragma endscop
}
