#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int row;
extern int NNTOT;
extern int col;
typedef float real;
extern real ** restrict Tmatrix;
extern real * restrict tempvecC;
extern int ** restrict vectors;
extern int vec;

void loop()
{
#pragma scop

    for(row = 0; row < NNTOT; ++row)
    {
        for(col = 0; col < NNTOT; ++col)
        {
            if(row == col) Tmatrix[row][col] = 0.0;
            else Tmatrix[row][col] += tempvecC[row] *((real )vectors[vec][col]);
        }
    }

#pragma endscop
}
