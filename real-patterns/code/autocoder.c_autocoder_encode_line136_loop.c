#include <inttypes.h>
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
extern float adder;
extern int h;

void loop()
{
#pragma scop

    for(int i = 0; i < autocoder -> NoOfInputs; i++)
    {
        adder += autocoder -> weights[h * autocoder -> NoOfInputs + i] * autocoder -> inputs[i];
    }

#pragma endscop
}
