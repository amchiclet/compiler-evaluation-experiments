#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double* restrict result;
extern double ** restrict mat1;
extern double* restrict mat2;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++)
    {
        for(j = 0; j < 4 * 4; j++)
        {
            result[i] += mat1[i][j] * mat2[j];
        }
    }

#pragma endscop
}
