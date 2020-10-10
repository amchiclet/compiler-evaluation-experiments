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
extern float f_bark_mid;
extern float step_barks;
extern float f_hz_mid;
extern float fsq;
extern float ftmp;
extern float  eql[100] ;

void loop()
{
#pragma scop

    for(i = pptr -> first_good; i < lastfilt; i++)
    {
        f_bark_mid = i * step_barks;
        f_hz_mid =(300. *(exp(((double )f_bark_mid) / 6.) - exp(-((double )f_bark_mid) / 6.)));
        fsq = f_hz_mid * f_hz_mid;
        ftmp =(fsq + 1.6e5);
        eql[i] = fsq / ftmp *(fsq / ftmp) *((fsq +((float )1.44e6)) /(fsq +((float )9.61e6)));
    }

#pragma endscop
}
