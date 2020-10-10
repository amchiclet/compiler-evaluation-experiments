#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
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
typedef struct
{
    ac *autocoder;
    int units_across;
    int units_down;
    float *convolution;
    int pooling_factor;
    float *pooling;
} deeplearn_conv_layer;
typedef struct
{
    unsigned int random_seed;
    int reduction_factor;
    int pooling_factor;
    int inputs_across;
    int inputs_down;
    int inputs_depth;
    int max_features;
    int no_of_layers;
    unsigned char enable_learning;
    deeplearn_conv_layer layer[100];
    int current_layer;
    float error_threshold[100];
    unsigned char training_complete;
    unsigned int itterations;
    float BPerror;
    unsigned int training_ctr;
    unsigned int history_plot_interval;
    char history_plot_filename[256];
    char history_plot_title[256];
    float history[1024];
    int history_index;
    int history_ctr;
    int history_step;
} deeplearn_conv;
extern deeplearn_conv * restrict conv;

void loop()
{
#pragma scop

    for(i = 0; i < conv -> history_index; i++)
    {
        conv -> history[i / 2] = conv -> history[i];
    }

#pragma endscop
}
