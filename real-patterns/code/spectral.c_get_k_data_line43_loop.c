#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int k;
extern double min;
extern int j;
extern int n;
extern int * restrict check;
extern double * restrict ev;
extern int index;
extern int l;
extern double ** restrict k_data;
extern double * restrict A;

void loop()
{
#pragma scop

    for(i = 0; i < k; i++)
    {
        min = 1.7976931348623157e+308;
        for(j = 0; j < n; j++)
        {
            if(check[j]) continue;
            else
            {
                if(ev[j] < min)
                {
                    min = ev[j];
                    index = j;
                }
            }
        }
        check[index] = 1;
        for(l = 0; l < n; l++) k_data[l][i] = A[l * n + index];
    }

#pragma endscop
}
