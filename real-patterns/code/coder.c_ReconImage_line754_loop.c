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
extern int cpels;
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

    for(n = 0; n < 16 >> 1; n++) for(m = 0; m < 16 >> 1; m++)
        {
            *(recon -> Cr +(x_curr >> 1) + m +((y_curr >> 1) + n) * cpels) = data -> Cr[n][m];
            *(recon -> Cb +(x_curr >> 1) + m +((y_curr >> 1) + n) * cpels) = data -> Cb[n][m];
        }

#pragma endscop
}
