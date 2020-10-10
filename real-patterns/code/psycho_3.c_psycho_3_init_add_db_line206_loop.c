#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double x;
struct psycho_3_mem_struct
{
    int off[2];
    int freq_subset[136];
    double bark[513];
    double ath[513];
    double fft_buf[2][1408];
    int cbands;
    int cbandindex[32];
    double dbtable[1000];
};

typedef struct psycho_3_mem_struct psycho_3_mem;
extern psycho_3_mem * restrict mem;

void loop()
{
#pragma scop

    for(i = 0; i < 1000; i++)
    {
        x =((double )i) / 10.0;
        mem -> dbtable[i] = 10 * log10(1 + pow(10.0,x / 10.0)) - x;
    }

#pragma endscop
}
