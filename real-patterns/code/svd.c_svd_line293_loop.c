#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int jj;
extern int m;
extern double y;
typedef struct
{
    int width;
    int height;
    float data[];
} F2D;
extern F2D * restrict input;
extern int j;
extern double z;
extern int i;
extern double c;
extern double s;

void loop()
{
#pragma scop

    for(jj = 0; jj < m; jj++)
    {
        y =((double )input -> data[jj * input -> width + j]);
        z =((double )input -> data[jj * input -> width + i]);
        input -> data[jj * input -> width + j] =((float )(y * c + z * s));
        input -> data[jj * input -> width + i] =((float )(z * c - y * s));
    }

#pragma endscop
}
