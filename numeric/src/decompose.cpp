#include<iostream>
#include<memory>

#include "mat_vec.h"

namespace numeric{
using namespace std;

template<typename T>
shared_ptr<Mat<T>> DoolittleDecompose(shared_ptr<Mat<T>> mat){
auto p = mat.Copy();
std::string str="DoolittleDecompose()";
std::cout<<str<<std::endl;
return p;
}

template<typename T>
shared_ptr<Mat<T>> HessenbergDecompose(shared_ptr<Mat<T>> mat){
auto p = mat->Copy();
std::string str="HessenbergDecompose()";
std::cout<<str<<std::endl;
return p;
}

template<typename T>
shared_ptr<Mat<T>> QRDecompose(shared_ptr<Mat<T>> mat){
auto p = mat.Copy();
std::string str="QRDecompose()";
std::cout<<str<<std::endl;
return p;
}

}
