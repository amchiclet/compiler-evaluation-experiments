#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
typedef struct
{
    int width;
    int height;
    int channels;
    double ***data;
} image;
typedef image * Image;
extern Image restrict im;
extern int i;
extern int c;
extern char ** restrict mask;
extern double mean;
extern double invlength;

void loop()
{
#pragma scop

    for(j = 0; j < im -> height; j++)
    {
        for(i = 0; i < im -> width; i++)
        {
            for(c = 0; c < im -> channels; c++)
            {
                if(!mask || mask[i][j])
                {
                    im -> data[i][j][c] =(im -> data[i][j][c] - mean) * invlength;
                }
                else
                {
                    im -> data[i][j][c] = 0.0;
                }
            }
        }
    }

#pragma endscop
}
