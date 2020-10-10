#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
struct map_param
{
    float reg_coef[32][256][256];
    float jah_set[32];
    int n_sets;
    int n_bands;
    int n_coefs;
    float boundaries[32];
};

extern struct map_param (* restrict mptr);
float jah_set[32];
int n_sets;
int n_bands;
int n_coefs;
float boundaries[32];
extern int j;
struct fmat
{
    float **values;
    int nrows;
    int ncols;
};

extern struct fmat* restrict map_source_ptr;

extern struct fvec
{
    float *values;
    int length;
}* restrict ras_nl_aspectrum;

extern struct param
{
    float winsize;
    int winpts;
    float stepsize;
    int steppts;
    int padInput;
    int sampfreq;
    int nframes;
    float nyqbar;
    int nfilts;
    int first_good;
    int trapezoidal;
    float winco;
    float polepos;
    int order;
    int nout;
    int gainflag;
    float lift;
    int lrasta;
    int jrasta;
    int cJah;
    char *mapcoef_fname;
    int crbout;
    int comcrbout;
    float rfrac;
    float jah;
    char *infname;
    char *num_fname;
    char *denom_fname;
    char *outfname;
    int ascin;
    int ascout;
    int espsin;
    int espsout;
    int matin;
    int matout;
    int spherein;
    int abbotIO;
    int inswapbytes;
    int outswapbytes;
    int debug;
    int smallmask;
    int online;
    int HPfilter;
    int history;
    char *hist_fname;
    int deltawindow;
    int deltaorder;
}* restrict pptr;

void loop()
{
#pragma scop

    for(i = 0; i < mptr -> n_bands; i++)
    {
        for(j = 0; j < mptr -> n_coefs - 1; j++)
        {
            map_source_ptr -> values[i][j] = ras_nl_aspectrum -> values[pptr -> first_good + j];
        }
        map_source_ptr -> values[i][mptr -> n_coefs - 1] = 1;
    }

#pragma endscop
}
