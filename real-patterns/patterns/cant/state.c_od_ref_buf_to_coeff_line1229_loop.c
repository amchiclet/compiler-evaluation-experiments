# induction variables converted

declare dst[];
declare src[];
declare coeff_shift;

for [y, x] {
  dst[y*dst_ystride + x] = (src[y*src_ystride + x] - 128) * (1 << coeff_shift);
}
