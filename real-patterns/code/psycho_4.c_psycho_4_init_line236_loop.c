#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  bark[513] ;
extern int cbase;
extern int partition_count;
extern int * restrict partition;
extern int * restrict numlines;

void loop()
{
#pragma scop

    for(i = 0; i < 513; i++)
    {
        if(bark[i] - bark[cbase] > 0.33)
        {
            cbase = i;
            partition_count++;
        }
        partition[i] = partition_count;
        numlines[partition_count]++;
    }

#pragma endscop
}
