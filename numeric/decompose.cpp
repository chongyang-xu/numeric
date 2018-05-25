#ifndef NUMERIC_DECOMPOSE_H
#define NUMERIC_DECOMPOSE_H
namespace numeric{

template<typename T>
shared_ptr<Mat<T>> DoolittleDecompose(shared_ptr<Mat<T>> mat);

template<typename T>
shared_ptr<Mat<T>> HessenbergDecompose(shared_ptr<Mat<T>> mat);

template<typename T>
shared_ptr<Mat<T>> QRDecompose(shared_ptr<Mat<T>> mat);

}
#endif
