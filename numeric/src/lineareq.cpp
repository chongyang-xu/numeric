#include<iostream>
#include<memory>

#include "mat_vec.h"
#include "decompose.h"
namespace numeric{
using namespace std;

template<typename T>
shared_ptr<Vec<T>> SolveLinearEqLU(shared_ptr<Mat<T>> A, shared_ptr<Vec<T>> b){
auto p = A.Copy();
auto q = b.get_m();
p->LUDecompose();
std::string str="SolveLinearEqLU()";
std::cout<<str<<std::endl;
return b;

}

template<typename T>
shared_ptr<Vec<T>> SolveLinearEqCG(shared_ptr<Mat<T>> A, shared_ptr<Vec<T>> b){
auto p = A.Copy();
auto q = b.get_m();
p->LUDecompose();
std::string str="SolveLinearEqCG()";
std::cout<<str<<std::endl;
return b;

}


}
