#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int num_terms;
typedef struct
{
    double alpha;
    double **log_prob_w;
    int num_topics;
    int num_terms;
} lda_model;
extern lda_model * restrict model;
extern int i;

void loop()
{
#pragma scop

    for(j = 0; j < num_terms; j++) model -> log_prob_w[i][j] = 0;

#pragma endscop
}
