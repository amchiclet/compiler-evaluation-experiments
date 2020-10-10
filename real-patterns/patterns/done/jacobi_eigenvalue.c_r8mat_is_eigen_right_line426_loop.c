declare c[];
declare a[];
declare x[];

for [small2, (small1, <=stride)] {
  c[small1 + small2 * stride] = 0.0;
  for [(small3, <=stride)] {
      c[small1 + small2 * stride] = c[small1 + small2 * stride] + a[small1 + small3 * stride] * x[small3 + small2 * stride];
  }
}
