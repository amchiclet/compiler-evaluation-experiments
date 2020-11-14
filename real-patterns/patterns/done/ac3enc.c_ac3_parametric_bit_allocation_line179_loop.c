declare psd[];
declare exp[];

for [bin] {
  psd[bin] = 3072 - (exp[bin] << 7);
}
