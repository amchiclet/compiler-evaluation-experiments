declare history_w[];
declare history_b[];

for [i] {
  history_w[i] = history_w[i] >> 8;
  history_b[i] = history_b[i] >> 8;
}
