#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nrows;
extern int* restrict rowstr;

void loop()
{
#pragma scop

    for(j = nrows; j >= 1; j--)
    {
        rowstr[j + 1] = rowstr[j];
    }

#pragma endscop
}
