#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nrows;
extern int* restrict rowstr;

void loop()
{
#pragma scop

    for(j = 2; j <= nrows + 1; j++)
    {
        rowstr[j] = rowstr[j] + rowstr[j - 1];
    }

#pragma endscop
}
