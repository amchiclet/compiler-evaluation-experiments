#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
struct autocode
{
    unsigned int random_seed;
    int NoOfInputs;
    int NoOfHiddens;
    float DropoutPercent;
    float *inputs;
    float *hiddens;
    float *outputs;
    float *weights;
    float *lastWeightChange;
    float *bias;
    float *lastBiasChange;
    float *bperr;
    float BPerror;
    float BPerrorPercent;
    float BPerrorAverage;
    float learningRate;
    float noise;
    unsigned int itterations;
};

typedef struct autocode ac;
extern ac * restrict autocoder;
extern float errorPercent;

void loop()
{
#pragma scop

    for(int i = 0; i < autocoder -> NoOfInputs; i++)
    {
        float BPerror = autocoder -> inputs[i] - autocoder -> outputs[i];
        autocoder -> BPerror += fabs(BPerror);
        errorPercent += fabs(BPerror);
        float afact = autocoder -> outputs[i] *(1.0f - autocoder -> outputs[i]);
        for(int h = 0; h < autocoder -> NoOfHiddens; h++)
        {
            if(autocoder -> hiddens[h] ==(- 9999)) continue;
            autocoder -> bperr[h] += BPerror * afact * autocoder -> weights[h * autocoder -> NoOfInputs + i];
        }
    }

#pragma endscop
}
