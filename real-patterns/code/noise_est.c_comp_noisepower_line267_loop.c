#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;

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
extern int lastfilt;
struct fmat
{
    float **values;
    int nrows;
    int ncols;
};

extern struct fmat* restrict all_trajec;
extern int t;
struct fvec
{
    float *values;
    int length;
};

extern struct fvec* restrict aspectrum;

void loop()
{
#pragma scop

    for(i = pptr -> first_good; i < lastfilt; i++) all_trajec -> values[i][t] =((float )(sqrt(((double )aspectrum -> values[i]))));

#pragma endscop
}
