#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int rows;
extern int j;
extern int cols;
typedef struct
{
    int width;
    int height;
    float data[];
} F2D;
extern F2D * restrict out;
extern float val;

void loop()
{
#pragma scop

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            out -> data[i * out -> width + j] = val;
        }
    }

#pragma endscop
}
