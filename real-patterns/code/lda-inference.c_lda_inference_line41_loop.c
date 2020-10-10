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
extern double ** restrict phi;
extern int k;
typedef struct
{
    double alpha;
    double **log_prob_w;
    int num_topics;
    int num_terms;
} lda_model;
extern lda_model * restrict model;

void loop()
{
#pragma scop

    for(n = 0; n < doc -> length; n++) phi[n][k] = 1.0 /(model -> num_topics);

#pragma endscop
}
