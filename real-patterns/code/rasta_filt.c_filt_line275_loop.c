#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
struct fvec
{
    float *values;
    int length;
};

extern struct fvec* restrict numer;
extern float sum;
struct fhistory
{
    float noiseOLD[100];
    float filtIN[100][25];
    float filtOUT[100][25];
    int normInit;
    int eos;
    int eof;
};

extern struct fhistory* restrict hptr;
extern int nfilt;

void loop()
{
#pragma scop

    for(j = 0; j < numer -> length; j++)
    {
        sum += numer -> values[j] * hptr -> filtIN[nfilt][j];
    }

#pragma endscop
}
