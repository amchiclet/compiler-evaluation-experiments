#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int l;

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
extern float sum;
extern float * restrict a;
extern int j;
extern int jb;
extern float * restrict c;

void loop()
{
#pragma scop

    for(l = 2; l < pptr -> nout; ++l)
    {
        if(l <= pptr -> order)
        {
            sum = l * a[l] / a[0];
        }
        else
        {
            sum = 0.;
        }
        for(j = 2; j <= l; ++j)
        {
            jb = l - j + 2;
            if(j <= pptr -> order + 1)
            {
                sum += a[j - 1] * c[jb - 1] *(jb - 1) / a[0];
            }
        }
        c[l] =(-((double )sum) / l);
    }

#pragma endscop
}
