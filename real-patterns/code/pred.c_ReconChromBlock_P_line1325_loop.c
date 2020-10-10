#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int m;
extern int ofx;
extern int x;
extern int xint;
extern int ofy;
extern int y;
extern int yint;
extern int pel;
struct pict_image
{
    unsigned char *lum;
    unsigned char *Cr;
    unsigned char *Cb;
};

typedef struct pict_image  PictImage;
extern PictImage * restrict prev;
extern int lx;
extern int xh;
struct mb_structure
{
    int lum[16][16];
    int Cr[8][8];
    int Cb[8][8];
};

typedef struct mb_structure  MB_Structure;
extern MB_Structure * restrict data;

void loop()
{
#pragma scop

    for(n = 0; n < 8; n++)
    {
        for(m = 0; m < 8; m++)
        {
            ofx = x + xint + m;
            ofy = y + yint + n;
            pel =( *(prev -> Cr + ofx + ofy * lx)) +( *(prev -> Cr + ofx + xh + ofy * lx)) + 1 >> 1;
            data -> Cr[n][m] += pel;
            pel =( *(prev -> Cb + ofx + ofy * lx)) +( *(prev -> Cb + ofx + xh + ofy * lx)) + 1 >> 1;
            data -> Cb[n][m] += pel;
        }
    }

#pragma endscop
}
