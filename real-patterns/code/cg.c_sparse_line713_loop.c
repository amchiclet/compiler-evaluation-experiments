#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int* restrict rowstr;
typedef int boolean;
extern int* restrict mark;

void loop()
{
#pragma scop

    for(j = 1; j <= n; j++)
    {
        rowstr[j] = 0;
        mark[j] = 0;
    }

#pragma endscop
}
