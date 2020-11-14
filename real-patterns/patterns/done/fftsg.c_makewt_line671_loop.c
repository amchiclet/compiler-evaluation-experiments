declare wk1r;
declare wk1i;
declare wk3r;
declare wk3i;
declare w[];

for [(j, +=4)] {
  wk1r = w[nw0 + 2 * j];
  wk1i = w[nw0 + 2 * j + 1];
  wk3r = w[nw0 + 2 * j + 2];
  wk3i = w[nw0 + 2 * j + 3];
  w[nw1 + j] = wk1r;
  w[nw1 + j + 1] = wk1i;
  w[nw1 + j + 2] = wk3r;
  w[nw1 + j + 3] = wk3i;
}
