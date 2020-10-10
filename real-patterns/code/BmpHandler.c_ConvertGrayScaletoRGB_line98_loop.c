#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int y;
extern int j;
extern int x;
extern int k;
extern int temp;
extern double *** restrict grayscale;
extern double min;
extern double max;
extern int imageIdx;
extern unsigned char * restrict bitmapImage;

void loop()
{
#pragma scop

    for(i = 0; i < y; i++) for(j = 0; j < x; j++) for(k = 0; k < 4 * 4; k++)
            {
                temp =((int )((grayscale[i + 1][j + 1][k] - min) * 255 /(max - min)));
                int Yindex = i * 4 +((int )(floor(((double )k) / 4)));
                int Xindex = j * 4 + k % 4;
                imageIdx = 3 *(x * 4 *(y * 4 - Yindex - 1) + Xindex);
                bitmapImage[imageIdx + 2] =((unsigned char )(298 *(temp - 16) + 128 >> 8));
                bitmapImage[imageIdx + 1] =((unsigned char )(298 *(temp - 16) + 128 >> 8));
                bitmapImage[imageIdx] =((unsigned char )(298 *(temp - 16) + 128 >> 8));
            }

#pragma endscop
}
