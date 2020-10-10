#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int jj;
extern int n;
extern double x;
typedef struct
{
    int width;
    int height;
    float data[];
} F2D;
extern F2D * restrict vOut;
extern int j;
extern double z;
extern int i;
extern double c;
extern double s;

void loop()
{
#pragma scop

    for(jj = 0; jj < n; jj++)
    {
        x =((double )vOut -> data[jj * vOut -> width + j]);
        z =((double )vOut -> data[jj * vOut -> width + i]);
        vOut -> data[jj * vOut -> width + j] =((float )(x * c + z * s));
        vOut -> data[jj * vOut -> width + i] =((float )(z * c - x * s));
    }

#pragma endscop
}
