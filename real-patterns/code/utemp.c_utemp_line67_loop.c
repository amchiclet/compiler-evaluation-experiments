#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned int i2;
extern double* restrict table1;
extern double* restrict table2;
extern double* restrict table3;

void loop()
{
#pragma scop

    for(i2 = 1; i2 <= 1023; i2++)
    {
        table1[i2] = exp(-((double )i2) / 8.0);
        table2[i2] = exp(-((double )i2) / 8192.0);
        table3[i2] = exp(-((double )i2) / 8388608.0);
    }

#pragma endscop
}
