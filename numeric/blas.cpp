#include"blas.h"

namespace numeric{
namespace blas{
//level 1
//single
void sscal(int N, float SA, float* SX){//SX in out
}
	
void scopy(int N, float* SX, float* SY){//SY out
}

void saxpy(int N, float SA, float* SX float* SY){//SY in out
}

float sdot(int N, float* SX, float* SY){
}

float snrm2(int N, float* X){

}
	
//level2
//single
void sgemv(bool TRANS, int M, int N, float ALPHA, float* A, float* X, float BETA, float* Y){//Y out

}
//level3
//single
void sgemm(bool TRANSA, bool TRANSB, int M, int N, int K, float ALPHA, float* A, float* B, float BETA, float* C){//C out

}


}//end blas
}//end numeric
#endif
