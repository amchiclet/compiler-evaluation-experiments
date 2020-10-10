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
        jet -> mag[i] = sqrt(jet -> realPart[i] * jet -> realPart[i] + jet -> imagPart[i] * jet -> imagPart[i]);
        if(jet -> realPart[i] != 0)
        {
            if(jet -> realPart[i] >= 0)
            {
                jet -> ang[i] = atan(jet -> imagPart[i] / jet -> realPart[i]);
            }
            else
            {
                jet -> ang[i] = 3.141592654 + atan(jet -> imagPart[i] / jet -> realPart[i]);
            }
        }
        else
        {
            if(jet -> imagPart[i] >= 0)
            {
                jet -> ang[i] = 3.141592654 / 2;
            }
            else
            {
                jet -> ang[i] = - 3.141592654 / 2;
            }
        }
    }

#pragma endscop
}
