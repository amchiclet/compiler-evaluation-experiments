declare pel;
declare prev_Cr[];
declare prev_Cb[];
declare data_Cr[][];
declare data_Cb[][];

for [n, m] {
  pel =
    prev_Cr[offset1 + offset2 + m + (offset3 + offset4 + n) * stride] +
    prev_Cr[offset1 + offset2 + m + (offset3 + offset4 + n + offset5) * stride] +
    1 >> 1;
  data_Cr[n][m] = data_Cr[n][m] + pel;
  pel =
    prev_Cb[offset1 + offset2 + m + (offset3 + offset4 + n) * stride] +
    prev_Cb[offset1 + offset2 + m + (offset3 + offset4 + n + offset5) * stride] +
    1 >> 1;
  data_Cb[n][m] = data_Cb[n][m] + pel;
}
