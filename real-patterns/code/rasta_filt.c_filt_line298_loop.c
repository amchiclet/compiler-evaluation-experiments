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

    for(j = numer -> length - 1; j > 0; j--)
    {
        hptr -> filtIN[nfilt][j] = hptr -> filtIN[nfilt][j - 1];
    }

#pragma endscop
}
