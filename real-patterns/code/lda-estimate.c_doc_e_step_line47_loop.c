#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
typedef struct
{
    int *words;
    int *counts;
    int length;
    int total;
} document;
extern document * restrict doc;
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
extern double ** restrict phi;

void loop()
{
#pragma scop

    for(n = 0; n < doc -> length; n++)
    {
        for(k = 0; k < model -> num_topics; k++)
        {
            ss -> class_word[k][doc -> words[n]] += doc -> counts[n] * phi[n][k];
            ss -> class_total[k] += doc -> counts[n] * phi[n][k];
        }
    }

#pragma endscop
}
