#include"polynomial.h"
#include"matrix.h"

#include<iostream>
using namespace numeric;
using namespace std;
int main() {
	Var1Polynomial<double> poly1(2);
	poly1.set(0, 1.0); poly1.set(1, 0.5);; poly1.set(2, 1.0);
	poly1.print();
	Var1Polynomial<double> poly1_2(poly1);
	poly1_2.print();

	Var1Polynomial<double> poly1_3 = poly1.addWithSameVar(poly1_2);
	poly1_3.print();

	Var1Polynomial<double> poly1_4 = poly1.mulWithSameVar(poly1_2);
	poly1_4.print();
	cout << "poly1_4(0) = " << poly1_4.eval(0) << endl;
	cout << "poly1_4(1) = " << poly1_4.eval(1) << endl;
	cout << "poly1_4(0.5) = " << poly1_4.eval(0.5) << endl;


	Matrix<double> mat(2, 3);
	mat.set(0, 0, 1); mat.set(0, 1, 2); mat.set(0, 2, 3);
	mat.set(1, 0, 5); mat.set(1, 1, 6); mat.set(1, 2, 7);
	Var2Polynomial<double> poly2(mat);
	poly2.print();
	cout << "poly2(0) = " << poly2.eval(0,0) << endl;
	cout << "poly2(1) = " << poly2.eval(1,2) << endl;
	cout << "poly2(0.5) = " << poly2.eval(0.5,0.13) << endl;

	system("pause");
	return 0;
}
