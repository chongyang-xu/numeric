#ifndef NUMERIC_LINEAREQ_H
#define NUMERIC_LINEAREQ_H
#include<memory>

#include "mat_vec.h"
namespace numeric{
using namespace std;

template<typename T>
shared_ptr<Vec<T>> SolveLinearEqLU(shared_ptr<Mat<T>> A, shared_ptr<Vec<T>> b);

template<typename T>
shared_ptr<Vec<T>> SolveLinearEqCG(shared_ptr<Mat<T>> A, shared_ptr<Vec<T>> b);

}
#endif

