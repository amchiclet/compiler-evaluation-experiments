#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int img_ty;
extern int img_by;
extern int patch_width;
extern int img_y_range;
extern int img_tx;
extern int img_bx;
extern int img_x_range;
extern int img_width;
extern int patch_depth;
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
extern int start_index;
extern unsigned char* restrict img;
extern float min_weight;
extern float weight_range;

void loop()
{
#pragma scop

    for(int y = img_ty; y < img_by; y++)
    {
        int patch_y =(y - img_ty) * patch_width / img_y_range;
        for(int x = img_tx; x < img_bx; x++)
        {
            int patch_x =(x - img_tx) * patch_width / img_x_range;
            int img_n =(y * img_width + x) * 3;
            int patch_n =(patch_y * patch_width + patch_x) * patch_depth;
            for(int c = 0; c < 3; c++)
            {
                float w = autocoder -> weights[start_index + patch_n + c * patch_depth / 3];
                img[img_n + c] =((unsigned char )((w - min_weight) * 255 / weight_range));
            }
        }
    }

#pragma endscop
}
