#ifndef NUMERIC_LINEAREQ_H
#define NUMERIC_LINEAREQ_H
namespace numeric{

template<typename T>
shared_ptr<Vec<T>> SolveLinearEqLU(shared_ptr<Mat<T>> A, shared_ptr<Vec<T>> b);

template<typename T>
shared_ptr<Vec<T>> SolveLinearEqCG(shared_ptr<Mat<T>> A, shared_ptr<Vec<T>> b);


}
#endif

