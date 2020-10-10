#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int lastrow;
extern int firstrow;
extern int k;
extern int  rowstr[14000 + 1 + 1] ;
extern int  colidx[14000 *(11 + 1) *(11 + 1) + 14000 *(11 + 2) + 1] ;
extern int firstcol;

void loop()
{
#pragma scop

    for(j = 1; j <= lastrow - firstrow + 1; j++)
    {
        for(k = rowstr[j]; k < rowstr[j + 1]; k++)
        {
            colidx[k] = colidx[k] - firstcol + 1;
        }
    }

#pragma endscop
}
