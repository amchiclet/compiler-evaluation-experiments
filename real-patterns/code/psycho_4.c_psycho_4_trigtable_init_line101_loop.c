#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef double  FCB[64];
typedef double  FHBLK[513];
typedef double  F2HBLK[2][513];
struct psycho_4_mem_struct
{
    int new;
    int old;
    int oldest;
    int flush;
    int sync_flush;
    int syncsize;
    double grouped_c[64];
    double grouped_e[64];
    double nb[64];
    double cb[64];
    double tb[64];
    double ecb[64];
    double bc[64];
    double cbval[64];
    double rnorm[64];
    double wsamp_r[1024];
    double phi[1024];
    double energy[1024];
    double window[1024];
    double ath[513];
    double thr[513];
    double c[513];
    double fthr[513];
    double absthr[513];
    int numlines[64];
    int partition[513];
    double *tmn;
    FCB *s;
    FHBLK *lthr;
    F2HBLK *r;
    F2HBLK *phi_sav;
    double snrtmp[2][32];
    double cos_table[6284];
};

typedef struct psycho_4_mem_struct psycho_4_mem;
extern psycho_4_mem * restrict p4mem;

void loop()
{
#pragma scop

    for(i = 0; i < 6284; i++)
    {
        p4mem -> cos_table[i] = cos(((double )i) / 2000.0);
    }

#pragma endscop
}
