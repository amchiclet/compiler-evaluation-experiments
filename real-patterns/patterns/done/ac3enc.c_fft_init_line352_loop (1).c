declare fft_rev[];
declare m;

for [i] {
  m = 0;
  for [(j, <=ln)] {
      m = m | ((i >> j & 1) << (ln + 1) - j - 1);
    }
  fft_rev[i] = m;
}
