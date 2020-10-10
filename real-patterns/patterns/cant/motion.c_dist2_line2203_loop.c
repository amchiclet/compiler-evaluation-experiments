declare p1[];
declare p1a[];
declare p2[];
declare v;
declare s;

for [j, i] {
  v = ((p1[(j-1)*stride + i] +
	p1[(j-1)*stride + i + 1] +
	p1a[j*stride + i] +
	p1a[j*stride + i + 1] +
	2) >> 2
       ) - p2[j*stride + i];
  s = s + v*v;
}
