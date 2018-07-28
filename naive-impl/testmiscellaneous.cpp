
//#include"miscellaneous.h"
#include"numbertable.h"
#include<iostream>
using namespace numeric;
using namespace std;

double f1(double* val, int num){
	return val[0]*val[0]*val[0];
}
double f2(double* val, int num) {
	return val[1] * val[1] ;
}
double f3(double* val, int num) {
	return 10 * sqrt(val[2]);
}

int main() {
	//DualQuadraticPiecewiseInterpolation
	NumberTableVar2<double> table(4,4);
	table.var1[0] = -1; table.var1[1] = 0; table.var1[2] = 1; table.var1[3] = 1.5;
	table.var2[0] = 0.5; table.var2[1] = 1; table.var2[2] = 1.5; table.var2[3] = 2;
	table.value->set(0, 0, 0.25); table.value->set(0, 1, 0.43); table.value->set(0, 2, 0.66);
	table.value->set(1, 0,  0.5); table.value->set(1, 1, 0.87); table.value->set(1, 2, 1.00);
	table.value->set(2, 0,    1); table.value->set(2, 1, 1.73); table.value->set(2, 2, 1.99);
/*
	table.print();
	double val = DualQuadraticPiecewiseInterpolation<double>(table, 0.3, 0.8);
	val = DualQuadraticPiecewiseInterpolation<double>(table, 1.4, 0.8);
	val = DualQuadraticPiecewiseInterpolation<double>(table, 1.6, 0.8);
	printf("f(0.3, 0.8) = %lf\n", val);

	//FixedPointIteration
	double ans[3] = { 0.6,0.6,0.1};
	double(*iter_vec[3])(double*,int) = { f1, f2, f3 };
	bool res = FixedPointIteration<double>(3, ans, iter_vec);
	if (!res) {
		printf("No Solution\n");
	}


	Var1Polynomial<double>** indepent_x_base = new Var1Polynomial<double>*[3 + 1];
	double arr[4] = { 1,2,3,4 };
	constructOrthogonalBase<double>(indepent_x_base, 3, arr, 4);
	*/
	system("pause");

	return 0;
}
