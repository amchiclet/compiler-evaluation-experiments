#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int l;
struct feature_node
{
    int index;
    double value;
};

struct problem
{
    int l;
    int n;
    double *y;
    struct feature_node **x;
    double bias;
};

struct tagl2r_l2_svc_fun
{
    double *C;
    double *z;
    double *D;
    int *I;
    int sizeI;
    const struct problem *prob;
};

extern struct tagl2r_l2_svc_fun* restrict this;
extern double * restrict y;
extern double f;

void loop()
{
#pragma scop

    for(i = 0; i < l; i++)
    {
        double d;
        this -> z[i] = y[i] * this -> z[i];
        d = 1 - this -> z[i];
        if(d > 0) f += this -> C[i] * d * d;
    }

#pragma endscop
}
