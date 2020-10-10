#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern float  output_range_min[1024] ;
extern float  output_range_max[1024] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1024; i++)
    {
        output_range_min[i] = 9999;
        output_range_max[i] =(- 9999);
    }

#pragma endscop
}
