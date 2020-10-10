declare d[];
declare s[];

for [j, i] {
  d[j*stride + i] = (d[j*stride + i] + s[j*stride + i] + 1) >> 1;
}
