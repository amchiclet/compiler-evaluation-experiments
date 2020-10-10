#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef struct
{
    double alpha;
    double **log_prob_w;
    int num_topics;
    int num_terms;
} lda_model;
extern lda_model * restrict model;
typedef struct
{
    double **class_word;
    double *class_total;
    double alpha_suffstats;
    int num_docs;
} lda_suffstats;
extern lda_suffstats * restrict ss;
extern int w;

void loop()
{
#pragma scop

    for(k = 0; k < model -> num_topics; k++)
    {
        ss -> class_total[k] = 0;
        for(w = 0; w < model -> num_terms; w++)
        {
            ss -> class_word[k][w] = 0;
        }
    }

#pragma endscop
}
