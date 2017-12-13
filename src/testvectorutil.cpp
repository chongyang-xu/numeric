#include"vectorutil.h"
#include"squarematrix.h"
using namespace numeric;

int mainoo() {
	double ans[3];
	double y[3] = { 1. , 2., 3. };
	double z[3] = { 3 , 2., 1. };
	SquareMatrix<double>*m = VectorUtil<double>::aMulTransB(y,z,3);
	m->printMatrix();
	m->transMulVec(y,z);
	delete m;
	double res = 	VectorUtil<double>::innerProduct(y,y,3);
	system("pause");
	return 0;
}