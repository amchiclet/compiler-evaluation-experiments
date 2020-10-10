#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int col;
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
extern int row;
extern double fConvolvedH;
extern double fConvolvedV;
extern int xxx;
extern int yyy;
extern int xxxDisp;
extern int iiMid;
extern int yyyDisp;
extern double fSampleH;
extern double fSampleV;
extern double * restrict uniformH;
extern double * restrict uniformV;
extern double elasticScale;

void loop()
{
#pragma scop

    for(col = 0; col < cmnistdoc -> m_cCols; ++col)
    {
        for(row = 0; row < cmnistdoc -> m_cRows; ++row)
        {
            fConvolvedH = 0.0;
            fConvolvedV = 0.0;
            for(xxx = 0; xxx < 21; ++xxx)
            {
                for(yyy = 0; yyy < 21; ++yyy)
                {
                    xxxDisp = col - iiMid + xxx;
                    yyyDisp = row - iiMid + yyy;
                    if(xxxDisp < 0 || xxxDisp >= cmnistdoc -> m_cCols || yyyDisp < 0 || yyyDisp >= cmnistdoc -> m_cRows)
                    {
                        fSampleH = 0.0;
                        fSampleV = 0.0;
                    }
                    else
                    {
                        int location = yyyDisp * cmnistdoc -> m_cCols + xxxDisp;
                        fSampleH = uniformH[location];
                        fSampleV = uniformV[location];
                    }
                    fConvolvedH += fSampleH * cmnistdoc -> m_GaussianKernel[yyy][xxx];
                    fConvolvedV += fSampleV * cmnistdoc -> m_GaussianKernel[yyy][xxx];
                }
            }
            int location = row * cmnistdoc -> m_cCols + col;
            cmnistdoc -> m_DispH[location] = elasticScale * fConvolvedH;
            cmnistdoc -> m_DispV[location] = elasticScale * fConvolvedV;
        }
    }

#pragma endscop
}
