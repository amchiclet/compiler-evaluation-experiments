#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict d;
extern int bo;
extern int w;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i || j) d[bo + i * w + j] = 0;
        }
    }

#pragma endscop
}
