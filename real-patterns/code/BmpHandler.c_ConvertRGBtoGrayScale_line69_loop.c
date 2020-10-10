#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int y;
extern int j;
extern int x;
extern double ** restrict grayscale;
extern unsigned char * restrict bitmapImage;
extern int imageIdx;

void loop()
{
#pragma scop

    for(i = 0; i < y; i++) for(j = 0; j < x; j++)
        {
            grayscale[y - i - 1][j] =((double )(66 * bitmapImage[imageIdx + 2] + 129 * bitmapImage[imageIdx + 1] + 25 * bitmapImage[imageIdx] + 128 >> 8));
            imageIdx += 3;
        }

#pragma endscop
}
