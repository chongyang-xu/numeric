#include"matrix.h"

#include<iostream>
using namespace numeric;
using namespace std;
int testmatrix() {
	Matrix<double> mat(2,3);
	mat.set(0,0,1); mat.set(0, 1, 2); mat.set(0, 2, 3);
	mat.set(1, 0, 5); mat.set(1, 1, 6); mat.set(1, 2, 7);
	cout << mat.get(0, 0) << endl;
	cout << mat.get(1, 2) << endl;
	cout << mat.getCol() << endl;
	cout << mat.getLine() << endl;
	cout << "mat" << endl;
	mat.printMatrix();

	Matrix<double> mat_2(mat);
	cout << "mat2" << endl;
	mat_2.printMatrix();
	Matrix<double>* p = mat_2.trans();
	cout << "transMat2" << endl;
	p->printMatrix();
	Matrix<double>* s = p->mul(&mat_2);
	cout << "S = transMat2 X Mat2" << endl;
	s->printMatrix();
	Matrix<double> t(3,3);
	t.set(0, 0,1); t.set(0, 1, 3); t.set(0, 2, 7);
	t.set(1, 0, 5); t.set(1, 1, 8); t.set(1, 2, 9);
	t.set(2, 0, 1); t.set(2, 1, 3); t.set(2, 2, 2);

	Matrix<double>* invT = t.inverse();
	cout << "invT" << endl;
	invT->printMatrix();
	delete invT;

	delete p;
	delete s;
	
	system("pause");
	return 0;
}