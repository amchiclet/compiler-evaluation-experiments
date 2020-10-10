#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;

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
extern double d_1;
extern double d_2;
extern float * restrict gexp;
extern float * restrict c;

void loop()
{
#pragma scop

    for(ii = 2; ii <= pptr -> nout; ++ii)
    {
        if((pptr -> lift) != 0.)
        {
            d_1 =((double )(ii - 1));
            d_2 =((double )(pptr -> lift));
            gexp[ii - 1] =(pow(d_1,d_2) * c[ii - 1]);
        }
        else
        {
            gexp[ii - 1] = c[ii - 1];
        }
    }

#pragma endscop
}
