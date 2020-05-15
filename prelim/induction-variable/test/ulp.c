#include "test/ulp.h"

float ulp(float f) {
  // convert to int representation
  unsigned int i = *(int*)(&f);

  // get the exponent part e
  unsigned int e = i << 1;
  e = e >> 24;

  // this float has the exponent = 2^(e-127) = 2^x
  unsigned int x = e - 127;

  // what's the smallest value 2^l with exponent 2^x
  // it's 2^(x-23), so l = x - 23
  unsigned int l = x - 23;

  // convert 2^l to a float

  // put this in the exponent part
  unsigned int ulp_i = (l + 127) << 23;

  // make it a float
  float ulp = *(float*)(&ulp_i);

  return ulp;
}
