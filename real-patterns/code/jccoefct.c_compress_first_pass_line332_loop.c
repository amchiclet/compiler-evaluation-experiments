#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int JDIMENSION;
extern JDIMENSION MCUindex;
extern JDIMENSION MCUs_across;
typedef short JCOEF;
extern JCOEF lastDC;
typedef JCOEF  JBLOCK[64];
typedef JBLOCK * JBLOCKROW;
extern JBLOCKROW restrict lastblockrow;
extern int h_samp_factor;
extern int bi;
extern JBLOCKROW restrict thisblockrow;

void loop()
{
#pragma scop

    for(MCUindex = 0; MCUindex < MCUs_across; MCUindex++)
    {
        lastDC = lastblockrow[h_samp_factor - 1][0];
        for(bi = 0; bi < h_samp_factor; bi++)
        {
            thisblockrow[bi][0] = lastDC;
        }
        thisblockrow += h_samp_factor;
        lastblockrow += h_samp_factor;
    }

#pragma endscop
}
