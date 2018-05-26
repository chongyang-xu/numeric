#include<iostream>
#include<memory>
#include<complex>

#include "mat_vec.h"
#include "decompose.h"
#include "lineareq.h"

namespace numeric {
using namespace std;

template<typename T>
shared_ptr<Vec<complex<T>>> QREigens(shared_ptr<Mat<T>> mat){
auto p = mat.Copy();
p->HessenbergDecompose();
std::string str="QREigens()";
std::cout<<str<<std::endl;
return nullptr;
}

template<typename T>
T PowerMaxEigen(shared_ptr<Mat<T>> mat, shared_ptr<Vec<T>> eigenvec){
auto p = mat.Copy();
auto q = eigenvec.get_m();
std::string str="PowerMaxEigen()";
std::cout<<str<<std::endl;
return p.get_m();
}

template<typename T>
T PowerMinEigen(shared_ptr<Mat<T>> mat, shared_ptr<Vec<T>> eigenvec){
auto p = mat.Copy();
HessenbergDecompose<float>(mat);
auto q = eigenvec.get_m();
SolveLinearEqLU(mat, eigenvec);
std::string str="PowerMinEigen()";
std::cout<<str<<std::endl;
return p.get_m();

}
template<>
float PowerMinEigen<float>(shared_ptr<Mat<float>> mat, shared_ptr<Vec<float>> eigenvec){
auto p = mat->Copy();
HessenbergDecompose<float>(mat);
auto q = eigenvec->get_m();
SolveLinearEqLU<float>(mat, eigenvec);
std::string str="PowerMinEigen()";
std::cout<<str<<std::endl;
return p->get_m();
}


}
