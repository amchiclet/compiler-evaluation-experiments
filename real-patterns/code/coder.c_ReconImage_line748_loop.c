#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int m;
struct pict_image
{
    unsigned char *lum;
    unsigned char *Cr;
    unsigned char *Cb;
};

typedef struct pict_image  PictImage;
extern PictImage * restrict recon;
extern int x_curr;
extern int y_curr;
extern int pels;
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

    for(n = 0; n < 16; n++) for(m = 0; m < 16; m++)
        {
            *(recon -> lum + x_curr + m +(y_curr + n) * pels) = data -> lum[n][m];
        }

#pragma endscop
}
