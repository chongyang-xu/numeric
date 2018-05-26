#ifndef NUMERIC_EIGEN_H
#define NUMERIC_EIGEN_H
#include<memory>
#include<complex>

#include"mat_vec.h"

namespace numeric {
using namespace std;

template<typename T>
shared_ptr<Vec<complex<T>>> QREigens(shared_ptr<Mat<T>> mat);

template<typename T>
T PowerMaxEigen(shared_ptr<Mat<T>> mat, shared_ptr<Vec<T>> eigenvec);

template<typename T>
T PowerMinEigen(shared_ptr<Mat<T>> mat, shared_ptr<Vec<T>> eigenvec);

}
#endif
