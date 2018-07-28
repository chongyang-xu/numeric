#ifndef NUMERIC_VECTOR_UTIL_H
#define NUMERIC_VECTOR_UTIL_H
#include "squarematrix.h"
#include "densematrix.h"

namespace numeric {

template<class T> class DenseMatrix;

template<class T>
class VectorUtil {
public:
	//endindex not included
	static double innerProduct(T u[], T v[], int begin_index, int end_index) {
		double res = 0.0;
		for (int i = begin_index; i < end_index; i++) {
			res += u[i] * v[i];
		}
		return res;
	}
	static double innerProduct(T u[], T v[], int dim) {
		return innerProduct(u, v, 0, dim);
	}
	static double squareNorm(T u[], int begin_index, int end_index) {
		return sqrt(innerProduct(u, u, begin_index, end_index));
	}
	static double squareNorm(T u[], int dim) {
		return sqrt(innerProduct(u, u, 0, dim));
	}
	static void vecScale(T u[],  double c, int dim) {
		for (int i = 0; i < dim; i++)
		{ 
			u[i] *= c;
		}
	}

	static DenseMatrix<T>* aMulTransB(T a[], T b[], int dim) {
		DenseMatrix<T> * res = new DenseMatrix<T>(dim);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				res->set(i, j, a[i] * b[j]);
			}
		}
		return res;
	}

private:
	VectorUtil() { ; }

};

}
#endif
