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
extern double sourceRow;
extern double sourceCol;
extern double fracRow;
extern double fracCol;
extern double w1;
extern double w2;
extern double w3;
extern double w4;
extern _Bool bSkipOutOfBounds;
extern int sRow;
extern int sCol;
extern int sRowp1;
extern int sColp1;
extern double sourceValue;
extern double * restrict inputVector;
extern double ** restrict mappedVector;

void loop()
{
#pragma scop

    for(row = 0; row < cmnistdoc -> m_cRows; ++row)
    {
        for(col = 0; col < cmnistdoc -> m_cCols; ++col)
        {
            int location = row * cmnistdoc -> m_cCols + col;
            sourceRow =((double )row) - cmnistdoc -> m_DispV[location];
            sourceCol =((double )col) - cmnistdoc -> m_DispH[location];
            fracRow = sourceRow -((int )sourceRow);
            fracCol = sourceCol -((int )sourceCol);
            w1 =(1.0 - fracRow) *(1.0 - fracCol);
            w2 =(1.0 - fracRow) * fracCol;
            w3 = fracRow *(1 - fracCol);
            w4 = fracRow * fracCol;
            bSkipOutOfBounds = 0;
            if(sourceRow + 1.0 >=(cmnistdoc -> m_cRows)) bSkipOutOfBounds = 1;
            if(sourceRow < 0) bSkipOutOfBounds = 1;
            if(sourceCol + 1.0 >=(cmnistdoc -> m_cCols)) bSkipOutOfBounds = 1;
            if(sourceCol < 0) bSkipOutOfBounds = 1;
            if(bSkipOutOfBounds == 0)
            {
                sRow =((int )sourceRow);
                sCol =((int )sourceCol);
                sRowp1 = sRow + 1;
                sColp1 = sCol + 1;
                while(sRowp1 >= cmnistdoc -> m_cRows)sRowp1 -= cmnistdoc -> m_cRows;
                while(sRowp1 < 0)sRowp1 += cmnistdoc -> m_cRows;
                while(sColp1 >= cmnistdoc -> m_cCols)sColp1 -= cmnistdoc -> m_cCols;
                while(sColp1 < 0)sColp1 += cmnistdoc -> m_cCols;
                int loc1 = sRow * cmnistdoc -> m_cCols + sCol;
                int loc2 = sRow * cmnistdoc -> m_cCols + sColp1;
                int loc3 = sRowp1 * cmnistdoc -> m_cCols + sCol;
                int loc4 = sRowp1 * cmnistdoc -> m_cCols + sColp1;
                sourceValue = w1 * inputVector[loc1] + w2 * inputVector[loc2] + w3 * inputVector[loc3] + w4 * inputVector[loc4];
            }
            else
            {
                sourceValue = 1.0;
            }
            mappedVector[row][col] = 0.5 *(1.0 - sourceValue);
        }
    }

#pragma endscop
}
