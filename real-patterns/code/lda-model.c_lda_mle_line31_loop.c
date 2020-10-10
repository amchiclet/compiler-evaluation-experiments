#include <inttypes.h>
#include <math.h>
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
extern int w;
typedef struct
{
    double **class_word;
    double *class_total;
    double alpha_suffstats;
    int num_docs;
} lda_suffstats;
extern lda_suffstats * restrict ss;

void loop()
{
#pragma scop

    for(k = 0; k < model -> num_topics; k++)
    {
        for(w = 0; w < model -> num_terms; w++)
        {
            if(ss -> class_word[k][w] > 0)
            {
                model -> log_prob_w[k][w] = log(ss -> class_word[k][w]) - log(ss -> class_total[k]);
            }
            else model -> log_prob_w[k][w] =(- 100);
        }
    }

#pragma endscop
}
