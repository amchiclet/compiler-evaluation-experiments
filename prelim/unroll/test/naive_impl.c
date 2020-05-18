#include "test/naive_impl.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int check_conv2d(
    const float *Oin,
    const float *I,
    const float *K,
    const float *actual,
    size_t H, size_t W, size_t C,
    size_t KH, size_t KW, size_t KC,
    size_t SH, size_t SW,
    size_t PT, size_t PB, size_t PL, size_t PR,
    size_t DH, size_t DW,
    float tolerance) {
  float *expected = malloc(H*W*C*sizeof(float));
  size_t IH = (H-1)*SH + (KH-1)*DH+1 - (PT+PB);
  size_t IW = (W-1)*SW + (KW-1)*DW+1 - (PL+PR);

  size_t granularity = 10000000;
  size_t total = H * W * C * KH * KW * KC;
  printf("Running naive impl: Total loops = %ld\n", total);
  size_t count = 0;

  // strides
  size_t O1 = W*C;
  size_t O2 = C;
  size_t O3 = 1;
  size_t K1 = KH*KW*KC;
  size_t K2 = KW*KC;
  size_t K3 = KC;
  size_t K4 = 1;
  size_t I1 = IW*KC;
  size_t I2 = KC;
  size_t I3 = 1;
  for (size_t h = 0; h < H; ++h) {
    for (size_t w = 0; w < W; ++w) {
      for (size_t c = 0; c < C; ++c) {
        expected[h*O1 + w*O2 + c*O3] = Oin[h*O1 + w*O2 + c*O3];
      }
    }
  }

  for (size_t h = 0; h < H; ++h) {
    for (size_t w = 0; w < W; ++w) {
      for (size_t c = 0; c < C; ++c) {
        float dot_prod = 0.0;
        for (size_t kh = 0; kh < KH; ++kh) {
          for (size_t kw = 0; kw < KW; ++kw) {
            for (size_t kc = 0; kc < KC; ++kc) {
              int ih = h*SH + kh*DH - PT;
              int iw = w*SW + kw*DW - PL;
              if (ih >= 0 && ih < (int)(IH) &&
                  iw >= 0 && iw < (int)(IW)) {
                dot_prod += I[ih*I1 + iw*I2 + kc*I3] * K[c*K1 + kh*K2 + kw*K3 + kc*K4];
              } else {
                printf("yeyy");
              }
              ++count;
              if (count % granularity == 0) {
                printf("Progress: %ld / %ld\n", count / granularity, total / granularity);
              }
            }
          }
        }
        expected[h*O1 + w*O2 + c*O3] += dot_prod;
      }
    }
  }

  int is_equal = 1;
  printf("Comparing\n");
  for (size_t h = 0; h < H; ++h) {
    for (size_t w = 0; w < W; ++w) {
      for (size_t c = 0; c < C; ++c) {
        float actual_v = actual[h*O1 + w*O2 + c*O3];
        float expected_v = expected[h*O1 + w*O2 + c*O3];
        float diff = actual_v - expected_v;
        if (fabs(diff) > tolerance) {
          is_equal = 0;
          printf("Actual(%.2f) Expected(%.2f)\n", actual_v, expected_v);
        }
      }
    }
  }

  free(expected);
  return is_equal;
}

int compare_3d(const float *expected, const float *actual,
               size_t n1_begin, size_t n1_end, size_t n1_array_size,
               size_t n2_begin, size_t n2_end, size_t n2_array_size,
               size_t n3_begin, size_t n3_end, size_t n3_array_size,
               float tolerance) {
  size_t stride3 = 1;
  size_t stride2 = stride3 * n3_array_size;
  size_t stride1 = stride2 * n2_array_size;

  int max_discrepency = 10;
  int n_discrepency = 0;
  printf("Comparing\n");
  for (size_t i = n1_begin; i < n1_end; ++i) {
    for (size_t j = n2_begin; j < n2_end; ++j) {
      for (size_t k = n3_begin; k < n3_end; ++k) {
        size_t index = i*stride1 + j*stride2 + k*stride3;
        float actual_v = actual[index];
        float expected_v = expected[index];
        float diff = actual_v - expected_v;
        if (fabs(diff) > tolerance) {
          printf("Actual(%.2f) Expected(%.2f)\n", actual_v, expected_v);
          ++n_discrepency;
          if (n_discrepency >= max_discrepency) {
            return 0;
          }
        }
      }
    }
  }
  return 1;
}

int check_conv2d_nchw(
    const float *Oin,
    const float *I,
    const float *K,
    const float *actual,
    size_t H, size_t W, size_t C,
    size_t KH, size_t KW, size_t KC,
    size_t SH, size_t SW,
    size_t PT, size_t PB, size_t PL, size_t PR,
    size_t DH, size_t DW,
    float tolerance) {
  float *expected = malloc(H*W*C*sizeof(float));
  size_t IH = (H-1)*SH + (KH-1)*DH+1 - (PT+PB);
  size_t IW = (W-1)*SW + (KW-1)*DW+1 - (PL+PR);

  size_t granularity = 10000000;
  size_t total = H * W * C * KH * KW * KC;
  printf("Running naive impl: Total loops = %ld\n", total);
  size_t count = 0;

  // strides
  size_t O1 = H*W;
  size_t O2 = W;
  size_t O3 = 1;
  size_t K1 = KC*KH*KW;
  size_t K2 = KH*KW;
  size_t K3 = KW;
  size_t K4 = 1;
  size_t I1 = IH*IW;
  size_t I2 = IW;
  size_t I3 = 1;
  for (size_t h = 0; h < H; ++h) {
    for (size_t w = 0; w < W; ++w) {
      for (size_t c = 0; c < C; ++c) {
        expected[c*O1 + h*O2 + w*O3] = Oin[c*O1 + h*O2 + w*O3];
      }
    }
  }

  for (size_t h = 0; h < H; ++h) {
    for (size_t w = 0; w < W; ++w) {
      for (size_t c = 0; c < C; ++c) {
        float dot_prod = 0.0;
        for (size_t kh = 0; kh < KH; ++kh) {
          for (size_t kw = 0; kw < KW; ++kw) {
            for (size_t kc = 0; kc < KC; ++kc) {
              int ih = h*SH + kh*DH - PT;
              int iw = w*SW + kw*DW - PL;
              if (ih >= 0 && ih < (int)(IH) &&
                  iw >= 0 && iw < (int)(IW)) {
                dot_prod += I[kc*I1 + ih*I2 + iw*I3] * K[c*K1 + kc*K2 + kh*K3 + kw*K4];
              } else {
                printf("yeyy");
              }
              ++count;
              if (count % granularity == 0) {
                printf("Progress: %ld / %ld\n", count / granularity, total / granularity);
              }
            }
          }
        }
        expected[c*O1 + h*O2 + w*O3] += dot_prod;
      }
    }
  }

  int is_equal = 1;
  printf("Comparing\n");
  for (size_t h = 0; h < H; ++h) {
    for (size_t w = 0; w < W; ++w) {
      for (size_t c = 0; c < C; ++c) {
        float actual_v = actual[c*O1 + h*O2 + w*O3];
        float expected_v = expected[c*O1 + h*O2 + w*O3];
        float diff = actual_v - expected_v;
        if (fabs(diff) > tolerance) {
          is_equal = 0;
          printf("Actual(%.2f) Expected(%.2f)\n", actual_v, expected_v);
        }
      }
    }
  }

  free(expected);
  return is_equal;
}

/* int check_himeno( */
/*     const float *A, */
/*     const float *B, */
/*     const float *C, */
/*     const float *BND, */
/*     const float *WRK1, */
/*     const float *WRK2, */
/*     const float *P, */
/*     float omega, */
/*     float gosa, */
/*     size_t I, size_t J, size_t K, */
/*     float tolerance) { */
/*   float *expected_wrk2 = malloc(I*J*K*sizeof(float)); */

/*   for(int i=1 ; i<I-1 ; ++i) { */
/*     for(int j=1 ; j<J-1 ; ++j) { */
/*       for(int k=1 ; k<K-1 ; ++k) { */
/*         // short index on a, b, c was moved up front */
/*         float s0 = */
/*             A[0][i][j][k] * P[i+1][j][k] + */
/*             A[1][i][j][k] * P[i][j+1][k] + */
/*             A[2][i][j][k] * P[i][j][k+1] */
/*             + */
/*             B[0][i][j][k] * (P[i+1][j+1][k] - P[i+1][j-1][k] - */
/*                              P[i-1][j+1][k] + P[i-1][j-1][k]) + */
/*             B[1][i][j][k] * (P[i][j+1][k+1] - P[i][j-1][k+1] - */
/*                              P[i][j+1][k-1] + P[i][j-1][k-1]) + */
/*             B[2][i][j][k] * (P[i+1][j][k+1] - P[i-1][j][k+1] - */
/*                              P[i+1][j][k-1] + P[i-1][j][k-1]) */
/*             + */
/*             C[0][i][j][k] * P[i-1][j][k] + */
/*             C[1][i][j][k] * P[i][j-1][k] + */
/*             C[2][i][j][k] * P[i][j][k-1] */
/*             + */
/*             WRK1[i][j][k]; */
/*         float ss = (s0 * A[3][i][j][k] - P[i][j][k]) * BND[i][j][k]; */
/*         gosa = gosa + ss*ss; */
/*         WRK2[i][j][k] = P[i][j][k] + omega * ss; */
/*       } */
/*     } */
/*   } */
/* } */