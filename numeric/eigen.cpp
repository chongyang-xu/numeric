#ifndef NUMERIC_EIGEN_H
#define NUMERIC_EIGEN_H
namespace numeric {
using shared_ptr = std::shared_ptr;
using complex = std::complex;
using vecotr  = std::vector;

template<typename T>
shared_ptr<Vec<T>> QREigens(shared_ptr<Mat<T>> mat);

template<typename T>
T PowerMaxEigen(shared_ptr<Mat<T>> mat, shared_ptr<Vec<T>> eigenvec);

template<typename T>
T PowerMinEigen(shared_ptr<Mat<T>> mat, shared_ptr<Vec<T>> eigenvec);

}
#endif
