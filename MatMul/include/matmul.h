#ifndef PARALLEL_MATMUL_H
#define PARALLEL_MATMUL_H

// one cpu thread dense mat mul
// C mn = A mk  *  B kn
// mat storage row major in malloc array
void STMatMulNaive(float* A, float* B, float* C, int m, int k, int n);
void STMatMulStupid(float* A, float* B, float* C, int m, int k, int n);
void STMatMul(float* A, float* B, float* C, int M, int N, int K);
void MTMatMul(float* A, float* B, float* C, int M, int N, int K);
void MatMulMKL(float* A, float* B, float*C, int M, int N, int K);

#endif
