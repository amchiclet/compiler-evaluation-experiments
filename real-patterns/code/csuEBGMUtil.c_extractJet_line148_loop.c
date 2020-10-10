#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    int length;
    double *wavelength;
    double *angle;
    double *phase;
    double *aspect;
    double *radius;
    int *size;
    double *kx;
    double *ky;
} gabor_jet_params;
typedef gabor_jet_params * GaborJetParams;
typedef struct
{
    int length;
    double x;
    double y;
    double *realPart;
    double *imagPart;
    double *mag;
    double *ang;
    GaborJetParams params;
} gabor_jet;
typedef gabor_jet * GaborJet;
extern GaborJet restrict jet;

void loop()
{
#pragma scop

    for(i = 0; i < jet -> length; i++)
    {
        jet -> realPart[i] = jet -> mag[i] * cos(jet -> ang[i]);
        jet -> imagPart[i] = jet -> mag[i] * sin(jet -> ang[i]);
    }

#pragma endscop
}
