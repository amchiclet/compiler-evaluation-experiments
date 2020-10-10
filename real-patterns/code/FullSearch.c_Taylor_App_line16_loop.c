#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int BlockSize;
extern int j;
extern double * restrict dfx;
typedef struct
{
    double *data;
    int x_length;
    int y_length;
} Image;
extern Image * restrict block_ref;
extern double * restrict dfy;
extern double * restrict z;
extern Image * restrict block;

void loop()
{
#pragma scop

    for(i = 0; i < BlockSize; i++)
    {
        for(j = 0; j < BlockSize; j++)
        {
            if(j == 0) dfx[i * BlockSize + j] = block_ref -> data[i * block_ref -> x_length + j + 1] - block_ref -> data[i * block_ref -> x_length + j];
            else if(j == BlockSize - 1) dfx[i * BlockSize + j] = block_ref -> data[i * block_ref -> x_length + j] - block_ref -> data[i * block_ref -> x_length + j - 1];
            else dfx[i * BlockSize + j] =(block_ref -> data[i * block_ref -> x_length + j + 1] - block_ref -> data[i * block_ref -> x_length + j - 1]) / 2;
            if(i == 0) dfy[i * BlockSize + j] = block_ref -> data[(i + 1) * block_ref -> x_length + j] - block_ref -> data[i * block_ref -> x_length + j];
            else if(i == BlockSize - 1) dfy[i * BlockSize + j] = block_ref -> data[i * block_ref -> x_length + j] - block_ref -> data[(i - 1) * block_ref -> x_length + j];
            else dfy[i * BlockSize + j] =(block_ref -> data[(i + 1) * block_ref -> x_length + j] - block_ref -> data[(i - 1) * block_ref -> x_length + j]) / 2;
            z[i * BlockSize + j] = block -> data[i * block -> x_length + j] - block_ref -> data[i * block_ref -> x_length + j];
        }
    }

#pragma endscop
}
