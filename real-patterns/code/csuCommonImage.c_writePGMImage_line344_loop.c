#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int x;
typedef struct
{
    int width;
    int height;
    int channels;
    double ***data;
} image;
typedef image * Image;
extern Image restrict im;
extern int y;
extern double pmax;
extern int channel;
extern double pmin;

void loop()
{
#pragma scop

    for(x = 0; x < im -> width; x++)
    {
        for(y = 0; y < im -> height; y++)
        {
            pmax =(im -> data[x][y][channel] < pmax?pmax : im -> data[x][y][channel]);
            pmin =(im -> data[x][y][channel] > pmin?pmin : im -> data[x][y][channel]);
        }
    }

#pragma endscop
}
