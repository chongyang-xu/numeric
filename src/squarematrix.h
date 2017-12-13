#ifndef NUMERIC_SQUARE_MATRIX_H
#define NUMERIC_SQUARE_MATRIX_H
#include<cstring>
#include<cstdio>
#include<algorithm>
namespace numeric {

template<class T>
class SquareMatrix {
public:
	virtual ~SquareMatrix() {};

	virtual T		get(int i, int j)  = 0;
	virtual void	set(int i, int j, T val) = 0;
	virtual int		getDim()  = 0;

	virtual double			det()  {
		SquareMatrix* m = LUDecompose();
		int dim = getDim();
		double res = 1.0;
		for (int i = 0; i < dim; i++) {
			res *= get(i, i);
		}
		delete m;
		return res;
	}
	virtual void			mulVec(T b[], T ans[])  {
		int dim = getDim();
		memset(ans, 0, sizeof(T)*dim);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				ans[i] += get(i, j)*b[j];
			}
		}
	}
	virtual void			transMulVec(T b[], T ans[]) {
		int dim = getDim();
		memset(ans, 0, sizeof(T)*dim);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {		
				ans[j] += get(i, j)*b[i];
			}
		}
	}
	
	virtual SquareMatrix<T>*	addI(T u)  = 0;
	virtual SquareMatrix<T>*	subMatrix(SquareMatrix<T>* another, double scale = 1.0) = 0;
	virtual SquareMatrix<T>*	mulMatrix(SquareMatrix<T>* another, double scale = 1.0) = 0;
	virtual SquareMatrix<T>*	getMatrix(int x, int y, int num) = 0;
	virtual void				setMatrix(int x, int y, SquareMatrix<T>* other) = 0;

	virtual SquareMatrix* LUDecompose()  = 0;
	virtual SquareMatrix* QRDecompose()  = 0;
	virtual SquareMatrix* QuasiUpperTriangularize()  = 0;
	virtual void solveEquation(T b[], T x[])  = 0;

	virtual void	printRawData()  = 0;
	virtual void	printMatrix()  = 0;
};
}
#endif
