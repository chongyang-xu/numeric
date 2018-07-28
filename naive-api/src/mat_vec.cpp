#include<iostream>
#include<memory>

#include "mat_vec.h"

namespace numeric{
using namespace std;

/*
 *  Mat func
 * 
 * */
template<typename T>
Mat<T>::Mat(int m, int n){
std::string str="Mat()";
std::cout<<str<<std::endl;
}

template<typename T>
Mat<T>::~Mat(){
std::string str="~Mat()";
std::cout<<str<<std::endl;
}

template<typename T>
int Mat<T>::get_m(){
std::string str="get_m()";
std::cout<<str<<std::endl;
return 0;
}

template<typename T>
int Mat<T>::get_n(){
std::string str="get_n()";
std::cout<<str<<std::endl;
return 0;
}

template<typename T>
void Mat<T>::operator[](int i){
std::string str="Mat[]()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Mat<T>> Mat<T>::Copy(){
std::string str="Mat<T>::Copy()";
std::cout<<str<<std::endl;
return nullptr;
}

template<typename T>
shared_ptr<Mat<T>> Mat<T>::Select(int m, int n, int beg, int end){
std::string str="Mat<T>::Select()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Mat<T>> Mat<T>::Add(shared_ptr<Mat<T>> b, shared_ptr<T> alpha){
std::string str="Mat<T>::Add()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Mat<T>> Mat<T>::Sub(shared_ptr<Mat<T>> b, shared_ptr<T> alpha){
std::string str="Mat<T>::Sub()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Mat<T>> Mat<T>::MulMat(shared_ptr<Mat<T>> b, shared_ptr<T> alpha, bool trans){
std::string str="Mat<T>::MulMat()";
std::cout<<str<<std::endl;
return nullptr;
}

template<typename T>
shared_ptr<Vec<T>> Mat<T>::MulVec(shared_ptr<Vec<T>> b, shared_ptr<T> alpha, bool trans){
std::string str="Mat<T>::MulVec()";
std::cout<<str<<std::endl;
return nullptr;
}

/*
 * Func on Mat
 * */
template<typename T>
shared_ptr<Mat<T>> Inverse(shared_ptr<Mat<T>> m){
std::string str="Inverse()";
std::cout<<str<<std::endl;
}

template<typename T>
T Det(shared_ptr<Mat<T>> m){
std::string str="Det()";
std::cout<<str<<std::endl;
}

template<typename T>
T Cond(shared_ptr<Mat<T>> m){
std::string str="Cond()";
std::cout<<str<<std::endl;
}

template<typename T>
T Rank(shared_ptr<Mat<T>> m){
std::string str="Rank()";
std::cout<<str<<std::endl;
}

template<typename T>
T Norm2(shared_ptr<Mat<T>> m){
std::string str="Norm2()";
std::cout<<str<<std::endl;
}

/*
 * Vec func
 * */
template<typename T>
Vec<T>:: Vec(int m){
std::string str="Vec()";
std::cout<<str<<std::endl;
}

template<typename T>
Vec<T>::~Vec(){
std::string str="~Vec()";
std::cout<<str<<std::endl;
}

template<typename T>
int Vec<T>::get_m(){
std::string str="Vec<T>::get_m()";
std::cout<<str<<std::endl;
return 0;
}
template<typename T>
void Vec<T>::operator [](int i){
std::string str="Vec<T>::[]()";
std::cout<<str<<std::endl;
}
template<typename T>
shared_ptr<Vec<T>> Vec<T>::Copy(){
std::string str="Vec<T>::Copy()";
std::cout<<str<<std::endl;
}

template<typename T>
void 	Vec<T>::Scale(T alpha){
std::string str="Scale()";
std::cout<<str<<std::endl;
}

template<typename T>
T	Vec<T>::Norm2(){
std::string str="Norm2()";
std::cout<<str<<std::endl;
}

template<typename T>
T	Vec<T>::Dot(shared_ptr<Vec<T>> b){
std::string str="Dot()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Mat<T>> Vec<T>::Out(shared_ptr<Vec<T>> b){
std::string str="Out()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Vec<T>>	Vec<T>::Add(shared_ptr<Vec<T>> b, shared_ptr<T> alpha=shared_ptr<T>()){
std::string str="Vec<T>::Add()";
std::cout<<str<<std::endl;
}

template<typename T>
shared_ptr<Vec<T>> Vec<T>::Sub(shared_ptr<Vec<T>> b, shared_ptr<T> alpha=shared_ptr<T>()){
std::string str="Vec<T>::Sub()";
std::cout<<str<<std::endl;
}

template class Mat<float>;
template class Mat<double>;

template class Vec<float>;
template class Vec<double>;



}

