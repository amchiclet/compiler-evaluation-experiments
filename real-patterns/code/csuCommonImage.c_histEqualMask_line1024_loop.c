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
extern int c;
extern char ** restrict mask;
extern double minVal;
extern double maxVal;
extern double totalPixels;

void loop()
{
#pragma scop

    for(x = 0; x < im -> width; x++)
    {
        for(y = 0; y < im -> height; y++)
        {
            for(c = 0; c < im -> channels; c++)
            {
                if(!mask || mask[x][y])
                {
                    minVal =(minVal > im -> data[x][y][c]?im -> data[x][y][c] : minVal);
                    maxVal =(maxVal < im -> data[x][y][c]?im -> data[x][y][c] : maxVal);
                    totalPixels += 1;
                }
            }
        }
    }

#pragma endscop
}
