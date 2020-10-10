#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
enum CUTOFF_NONE_enum {CUTOFF_NONE=0,CUTOFF_SIMPLE=1,CUTOFF_ENERGY=2,CUTOFF_STRETCH=3,CUTOFF_CLASSES=4};;
typedef enum CUTOFF_NONE_enum CutOffMode;
typedef struct
{
    int numSubjects;
    int numPixels;
    int basisDim;
    Matrix values;
    Matrix basis;
    Matrix mean;
    int useLDA;
    CutOffMode cutOffMode;
    double cutOff;
    int dropNVectors;
} Subspace;
extern Subspace * restrict s;
extern double deltaSumOfSquares;
extern Matrix restrict deltaCentered;

void loop()
{
#pragma scop

    for(i = 0; i < s -> numPixels; i++) deltaSumOfSquares += deltaCentered -> cols[0][i] * deltaCentered -> cols[0][i];

#pragma endscop
}
