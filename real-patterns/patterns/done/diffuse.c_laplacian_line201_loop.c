declare tm2[][][];
declare u[][][];
declare wdtdr[][];

for [small1, small2, small3, small4] {
  tm2[small1][small3][small4] =
    tm2[small1][small3][small4] +
    u[small1][small2][small4] * wdtdr[small3][small2];
}
