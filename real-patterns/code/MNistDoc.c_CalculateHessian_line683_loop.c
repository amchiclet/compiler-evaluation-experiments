#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
struct Preferences
{
    unsigned int m_nItemsTrainingLabels;
    unsigned int m_nItemsTrainingImages;
    unsigned int m_nItemsTestingLabels;
    unsigned int m_nItemsTestingImages;
    int g_cImageSize;
    int m_nRowsImages;
    int m_nColsImages;
    int m_nMagWindowSize;
    int m_nMagWindowMagnification;
    double m_dInitialEtaLearningRate;
    double m_dLearningRateDecay;
    double m_dMinimumEtaLearningRate;
    unsigned int m_nAfterEveryNBackprops;
    double m_dMicronLimitParameter;
    unsigned int m_nNumHessianPatterns;
    double m_dMaxScaling;
    double m_dMaxRotation;
    double m_dElasticSigma;
    double m_dElasticScaling;
};

typedef struct Preferences  Preferences;
extern Preferences * restrict p;
extern int jj;
extern double  inputVector[841] ;
extern unsigned char  grayLevels[784] ;

void loop()
{
#pragma scop

    for(ii = 0; ii < p -> g_cImageSize; ++ii)
    {
        for(jj = 0; jj < p -> g_cImageSize; ++jj)
        {
            inputVector[1 + jj + 29 *(ii + 1)] =((double )((int )((unsigned char )grayLevels[jj + p -> g_cImageSize * ii]))) / 128.0 - 1.0;
        }
    }

#pragma endscop
}
