#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int row;
struct vector
{
    void **items;
    int capacity;
    int total;
};

typedef struct vector  vector;
struct VectorLayers
{
    vector *Layers;
};

struct NeuralNetwork
{
    volatile double m_etaLearningRatePrevious;
    volatile double m_etaLearningRate;
    volatile unsigned int m_cBackprops;
    struct VectorLayers *m_Layers;
};

typedef struct NeuralNetwork  NeuralNetwork;
typedef struct
{
    double *m_DispH;
    double *m_DispV;
    double m_GaussianKernel[21][21];
    int m_cCols;
    int m_cRows;
    int m_cCount;
    volatile unsigned int m_cBackprops;
    volatile _Bool m_bNeedHessian;
    unsigned int m_nAfterEveryNBackprops;
    double m_dEtaDecay;
    double m_dMinimumEta;
    volatile double m_dEstimatedCurrentMSE;
    FILE *m_fileTrainingLabels;
    FILE *m_fileTrainingImages;
    FILE *m_fileTestingLabels;
    FILE *m_fileTestingImages;
    _Bool m_bDistortTrainingPatterns;
    volatile unsigned int m_iNextTrainingPattern;
    volatile unsigned int m_iRandomizedTrainingPatternSequence[60000];
    int g_cImageSize;
    _Bool m_bDistortTestingPatterns;
    unsigned int m_iWhichImageSet;
    unsigned int m_nItemsTrainingImages;
    unsigned int m_nItemsTestImages;
    volatile unsigned int m_iNextTestingPattern;
    NeuralNetwork *m_NN;
} CMNistDoc;
extern CMNistDoc * restrict cmnistdoc;
extern int col;
extern double dSFHoriz;
extern int iMid;
extern double dSFVert;

void loop()
{
#pragma scop

    for(row = 0; row < cmnistdoc -> m_cRows; ++row)
    {
        for(col = 0; col < cmnistdoc -> m_cCols; ++col)
        {
            int location = row * cmnistdoc -> m_cCols + col;
            cmnistdoc -> m_DispH[location] += dSFHoriz *(col - iMid);
            cmnistdoc -> m_DispV[location] -= dSFVert *(iMid - row);
        }
    }

#pragma endscop
}
