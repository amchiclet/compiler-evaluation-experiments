#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef short int16_t;
typedef int16_t od_dering_in;
extern od_dering_in * restrict img;
extern int stride;
extern int coeff_shift;
extern int  partial[8][15] ;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        int j;
        for(j = 0; j < 8; j++)
        {
            int x;
            x = img[i * stride + j] >> coeff_shift;
            partial[0][i + j] += x;
            partial[1][i + j / 2] += x;
            partial[2][i] += x;
            partial[3][3 + i - j / 2] += x;
            partial[4][7 + i - j] += x;
            partial[5][3 - i / 2 + j] += x;
            partial[6][j] += x;
            partial[7][i / 2 + j] += x;
        }
    }

#pragma endscop
}
