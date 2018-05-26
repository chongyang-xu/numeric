#include<iostream>
#include<memory>

#include"blas.h"

namespace numeric{
namespace blas{
//level 1
//single
void sscal(int N, float SA, float* SX){//SX in out
std::string str="sscal()";
std::cout<<str<<std::endl;;
}
	
void scopy(int N, float* SX, float* SY){//SY out
std::string str="scopy()";
std::cout<<str<<std::endl;
}

void saxpy(int N, float SA, float* SX, float* SY){//SY in out
std::string str="saxpy()";
std::cout<<str<<std::endl;
}

float sdot(int N, float* SX, float* SY){
std::string str="sdot()";
std::cout<<str<<std::endl;
return .0;
}

float snrm2(int N, float* X){
std::string str="snrm2()";
std::cout<<str<<std::endl;
return .0;
}
	
//level2
//single
void sgemv(bool TRANS, int M, int N, float ALPHA, float* A, float* X, float BETA, float* Y){//Y out
std::string str="sgemv()";
std::cout<<str<<std::endl;;	
}
//level3
//single
void sgemm(bool TRANSA, bool TRANSB, int M, int N, int K, float ALPHA, float* A, float* B, float BETA, float* C){//C out
std::string str="sgemm()";
std::cout<<str<<std::endl;
}


}//end blas
}//end numeric
