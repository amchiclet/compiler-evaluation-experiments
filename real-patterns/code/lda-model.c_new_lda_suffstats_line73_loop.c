#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int num_terms;
typedef struct
{
    double **class_word;
    double *class_total;
    double alpha_suffstats;
    int num_docs;
} lda_suffstats;
extern lda_suffstats * restrict ss;
extern int i;

void loop()
{
#pragma scop

    for(j = 0; j < num_terms; j++)
    {
        ss -> class_word[i][j] = 0;
    }

#pragma endscop
}
