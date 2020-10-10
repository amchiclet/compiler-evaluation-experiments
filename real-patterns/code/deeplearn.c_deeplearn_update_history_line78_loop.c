#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
struct bp_n
{
    int NoOfInputs;
    float *weights;
    float *lastWeightChange;
    struct bp_n **inputs;
    float min_weight;
    float max_weight;
    float bias;
    float lastBiasChange;
    float BPerror;
    int excluded;
    float value;
    float value_reprojected;
    float desiredValue;
};

typedef struct bp_n bp_neuron;
struct backprop
{
    int NoOfInputs;
    int NoOfHiddens;
    int NoOfOutputs;
    int HiddenLayers;
    float DropoutPercent;
    bp_neuron **inputs;
    bp_neuron ***hiddens;
    bp_neuron **outputs;
    float BPerrorTotal;
    float BPerror;
    float BPerrorAverage;
    float BPerrorPercent;
    float learningRate;
    float noise;
    unsigned int random_seed;
    unsigned int itterations;
};

typedef struct backprop bp;
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
struct deeplearndata
{
    float *inputs;
    char **inputs_text;
    float *outputs;
    unsigned int flags;
    unsigned int labeled;
    struct deeplearndata *prev;
    struct deeplearndata *next;
};

typedef struct deeplearndata deeplearndata;
struct deeplearndata_meta
{
    deeplearndata *sample;
    struct deeplearndata_meta *prev;
    struct deeplearndata_meta *next;
};

typedef struct deeplearndata_meta deeplearndata_meta;
struct deepl
{
    bp *net;
    ac **autocoder;
    int current_hidden_layer;
    float BPerror;
    unsigned int itterations;
    float *error_threshold;
    int training_complete;
    int no_of_input_fields;
    int *field_length;
    deeplearndata *data;
    int data_samples;
    deeplearndata **indexed_data;
    int indexed_data_samples;
    deeplearndata_meta *training_data;
    int training_data_samples;
    deeplearndata_meta **indexed_training_data;
    int indexed_training_data_samples;
    deeplearndata_meta *training_data_labeled;
    int training_data_labeled_samples;
    deeplearndata_meta **indexed_training_data_labeled;
    int indexed_training_data_labeled_samples;
    deeplearndata_meta *test_data;
    int test_data_samples;
    deeplearndata_meta **indexed_test_data;
    int indexed_test_data_samples;
    float *input_range_min;
    float *input_range_max;
    float *output_range_min;
    float *output_range_max;
    unsigned int training_ctr;
    unsigned int history_plot_interval;
    char history_plot_filename[256];
    char history_plot_title[256];
    float history[1024];
    int history_index;
    int history_ctr;
    int history_step;
};

typedef struct deepl deeplearn;
extern deeplearn * restrict learner;

void loop()
{
#pragma scop

    for(i = 0; i < learner -> history_index; i++)
    {
        learner -> history[i / 2] = learner -> history[i];
    }

#pragma endscop
}
