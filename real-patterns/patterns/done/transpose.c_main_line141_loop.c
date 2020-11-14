declare B_p[];

for [(j, >=0, <=order), (i, >=0, <=order)] {
  B_p[i + (order + 1) * j] = - 1.0;
}
