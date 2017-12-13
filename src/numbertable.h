#ifndef NUMERIC_NUMBER_TABLE_H
#define NUMERIC_NUMBER_TABLE_H
#include"matrix.h"
namespace numeric {
template<class T>
struct NumberTableVar2 {
	/*	Êý±í
	| x0 | x1 | x2 | x3 |
	|y0|  z00   z10  z20  z30
	|y1|  z01   z11  z21  z31
	|y2|  z02   z12  z22  z32

	*/
	NumberTableVar2(int dim_1, int dim_2) {
		dim1 = dim_1;
		dim2 = dim_2;
		var1 = new T[dim_1];
		memset(var1,0, sizeof(T)*dim1);
		var2 = new T[dim_2];
		memset(var2, 0, sizeof(T)*dim2);
		value = new Matrix<T>(dim_1, dim_2);
	}
	~NumberTableVar2() {
		delete[]var1;
		delete[]var2;
		delete value;
	}
	void print() {
		printf("\t");
		for (int j = 0; j < dim2; j++) {
			printf("\ty%d=%lf", j, var2[j]);
		}
		printf("\n\n");
		for (int i = 0; i < dim1; i++) {
			printf("x%d=%lf\t", i,var1[i]);
			for (int j = 0; j < dim2; j++) {
				printf("%lf\t", value->get(i,j));
			}
			printf("\n");
		}
	}
	T* var1;
	T* var2;
	Matrix<T>* value;
	int dim1;
	int dim2;
};
}
#endif // !NUMERIC_NUMBER_TABLE_H

