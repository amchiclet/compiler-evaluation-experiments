#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int nza;
extern int nnza;
extern int j;
extern int* restrict arow;
extern int firstrow;
extern int* restrict rowstr;

void loop()
{
#pragma scop

    for(nza = 1; nza <= nnza; nza++)
    {
        j = arow[nza] - firstrow + 1 + 1;
        rowstr[j] = rowstr[j] + 1;
    }

#pragma endscop
}
