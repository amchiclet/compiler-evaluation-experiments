declare A[] ;
declare dfx[];
declare dfy[];
declare rhs[] ;
declare z[];

for [(i, >=0, <=BlockSize), (j, >=0, <=BlockSize)] {
  A[0] = A[0] + dfx[i * (BlockSize+1) + j] * dfx[i * (BlockSize+1) + j];
  A[1] = A[1] + dfx[i * (BlockSize+1) + j] * dfy[i * (BlockSize+1) + j];
  A[2] = A[1];
  A[3] = A[3] + dfy[i * (BlockSize+1) + j] * dfy[i * (BlockSize+1) + j];
  rhs[0] = rhs[0] + z[i * (BlockSize+1) + j] * dfx[i * (BlockSize+1) + j];
  rhs[1] = rhs[1] + z[i * (BlockSize+1) + j] * dfy[i * (BlockSize+1) + j];
}
