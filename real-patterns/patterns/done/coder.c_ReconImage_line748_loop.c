declare recon_lum[];
declare data_lum[][];

for [n, m] {
  recon_lum[offset1 + m + (offset2 + n) * stride] = data_lum[n][m];
}
