#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int time;
struct fvec
{
    float *values;
    int length;
};

extern struct fvec* restrict filter;
extern float time_constant;
extern float sum;

void loop()
{
#pragma scop

    for(i = 1; i < time; i++)
    {
        filter -> values[i] =((float )(-pow(((double )time_constant),((double )i))));
        sum += fabs(((double )filter -> values[i]));
    }

#pragma endscop
}
