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
struct fvec
{
    float *values;
    int length;
};

extern struct fvec* restrict nl_audptr;
extern struct fvec* restrict audspec;

void loop()
{
#pragma scop

    for(i = pptr -> first_good; i < lastfilt; i++)
    {
        if(pptr -> jrasta)
        {
            nl_audptr -> values[i] =(log(1.0 +(pptr -> jah * audspec -> values[i])));
        }
        else if(pptr -> lrasta)
        {
            if(audspec -> values[i] < 1.0e-45)
            {
                audspec -> values[i] = 1.0e-45;
            }
            nl_audptr -> values[i] =(log(audspec -> values[i]));
        }
        else
        {
            nl_audptr -> values[i] = audspec -> values[i];
        }
    }

#pragma endscop
}
