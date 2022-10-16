#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int IFH;
extern int IFHP;
extern int IFM;
extern int IFW;
extern int IFWP;
extern int IMG;
extern int KH;
extern int KW;
extern int OFH;
extern int OFM;
extern int OFW;
extern int PH;
extern int PW;
extern int SH;
extern int SW;

int core(double (*restrict filter)[((((((OFM / 4) * IFM) / 4) * KH) * KW) * 4) * 4], double (*restrict input)[((((IMG * IFM) / 4) * IFHP) * IFWP) * 4], double (*restrict output)[((((IMG * OFM) / 4) * OFH) * OFW) * 4]) {
int ii;
int ij;
int input_ifm_stride;
int input_img_stride;
int ki_begin;
int ki_end;
int kj_begin;
int kj_end;
int output_img_stride;
int output_ofm_stride;
int weight_ifm_stride;
int weight_ofm_stride;
  input_img_stride = (IFM * IFHP) * IFWP;
  input_ifm_stride = (IFHP * IFWP) * 4;
  output_img_stride = (OFM * OFH) * OFW;
  output_ofm_stride = (OFH * OFW) * 4;
  weight_ofm_stride = ((IFM * KH) * KW) * 4;
  weight_ifm_stride = ((KH * KW) * 4) * 4;
  for (int img = 0; img <= IMG - 1; img += 1) {
    for (int ifm_tile = 0; ifm_tile <= IFM / 4 - 1; ifm_tile += 1) {
      for (int ofm_tile = 0; ofm_tile <= OFM / 4 - 1; ofm_tile += 1) {
        for (int ofm = 0; ofm <= 4 - 1; ofm += 1) {
          for (int oj = 0; oj <= OFH - 1; oj += 1) {
            ij = oj * SH - PH;
            kj_begin = ij < 0 ? 0 - ij : 0;
            kj_end = (ij + KH) - 1 >= IFH ? ((ij + KH) - IFH) + 1 : KH;
            for (int oi = 0; oi <= OFH - 1; oi += 1) {
              ii = oi * SW - PW;
              ki_begin = ii < 0 ? 0 - ii : 0;
              ki_end = (ii + KW) - 1 > IFW ? ((ii + KW) - IFW) + 1 : KW;
              for (int kj = kj_begin; kj <= kj_end - 1; kj += 1) {
                for (int ki = ki_begin; ki <= ki_end - 1; ki += 1) {
                  for (int ifm = 0; ifm <= 4 - 1; ifm += 1) {
                    (*input)[(((img * input_img_stride + ifm_tile * input_ifm_stride) + (((ij + kj) + PH) * IFWP) * 4) + ((ii + ki) + PW) * 4) + ifm] = (*input)[(((img * input_img_stride + ifm_tile * input_ifm_stride) + (((ij + kj) + PH) * IFWP) * 4) + ((ii + ki) + PW) * 4) + ifm] + (*output)[(((img * output_img_stride + ofm_tile * output_ofm_stride) + (oj * OFW) * 4) + oi * 4) + ofm] * (*filter)[((((ofm_tile * weight_ofm_stride + ifm_tile * weight_ifm_stride) + ((kj * KW) * 4) * 4) + (ki * 4) * 4) + ofm * 4) + ifm];
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
