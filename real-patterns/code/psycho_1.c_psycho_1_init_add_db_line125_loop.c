#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double x;
typedef struct
{
    double x;
    int type;
    int next;
    int map;
}** mask_ptr;
typedef struct
{
    int line;
    double bark;
    double hear;
    double x;
}** g_ptr;
struct psycho_1_mem_struct
{
    int off[2];
    double fft_buf[2][1408];
    int *cbound;
    int crit_band;
    int sub_size;
    mask_ptr power;
    g_ptr ltg;
    double dbtable[1000];
};

typedef struct psycho_1_mem_struct psycho_1_mem;
extern psycho_1_mem * restrict mem;

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
