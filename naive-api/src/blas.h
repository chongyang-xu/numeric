#ifndef NUMERIC_BLAS_H
#define NUMERIC_BLAS_H

namespace numeric{
namespace blas{
/*
	//level 1
	//single
	void sscal(int N, float SA, float* SX, int INCX);//SX in out
	void scopy(int N, float* SX, int INCX, float* SY, int INCY);//SY out
	void saxpy(int N, float SA, float* SX, int INCX, float* SY, int INCY);//SY in out
	float sdot(int N, float* SX, int INCX, float* SY, int INCY);
	float snrm2(int N, float* X, int INCX);
	
	//level2
	//single
	void sgemv(char TRANS, int M, int N, float ALPHA, float* A, int LDA, float* X, int INCX, float BETA, float* Y, int INCY);//Y out

	//level3
	//single
	void sgemm(char TRANSA, char TRANSB, int M, int N, int K, float ALPHA, float* A, int LDA, float* B, int LDB, float BETA, float* C, int LDC);//C out
*/

	//level 1
	//single
	void sscal(int N, float SA, float* SX);//SX in out
	void scopy(int N, float* SX, float* SY);//SY out
	void saxpy(int N, float SA, float* SX, float* SY);//SY in out
	float sdot(int N, float* SX, float* SY);
	float snrm2(int N, float* X);
	
	//level2
	//single
	void sgemv(bool TRANS, int M, int N, float ALPHA, float* A, float* X, float BETA, float* Y);//Y out

	//level3
	//single
	void sgemm(bool TRANSA, bool TRANSB, int M, int N, int K, float ALPHA, float* A, float* B, float BETA, float* C);//C out

}
}
#endif
