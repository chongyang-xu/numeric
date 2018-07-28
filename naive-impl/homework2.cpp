#include"densematrix.h"
#include"eigensolver.h"
#include<cstdio>
#include<complex>
#include<cmath>
#include<iostream>

void pivotGausselimination(numeric::SquareMatrix<double>* A, double ans[], double b[]);

int main() {
	numeric::DenseMatrix<double> A(10);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i != j) {
				double val = sin( 0.5*(i + 1) + 0.2*(j + 1) );
				A.set(i, j,  val);
			}
			else {
				double val = 1.52*cos(i + 1 + 1.2*(j + 1));
				A.set(i, j, val);
			}
		}
	}

	printf("\n============拟上三角矩阵==================\n");
	numeric::SquareMatrix<double>* tri = A.QuasiUpperTriangularize();
	tri->printMatrix();
	delete tri;

	printf("\n============QR方法迭代结束后矩阵============\n");
	std::complex<double> engin_vals[10];
	numeric::EigenSolver<double> solver(&A, 1e-12, 1.0e8);
	numeric::SquareMatrix<double>* qr =  solver.QRMethod(engin_vals);
	qr->printMatrix();
	delete qr;

	printf("\n============全部特征值为===================\n");
	for (int i = 0; i < 10; i++) {
		double* s = (double*)&engin_vals[i];
		printf("lambada_%d : (%+.12e, %+.12e)\n", i, s[0], s[1]);
	}

	printf("\n============实特征值对应向量================\n");
	for (int i = 0; i < 10; i++) {
		double* s = (double*)&engin_vals[i];
		double egin_vec[10];
		double b[10] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0. };
		if (fabs(s[1]) <= 1e-12) {
			printf("lambada_%d : (%+.12e, %+.12e)\n", i, s[0], s[1]);
			numeric::SquareMatrix<double>*tmp = A.addI(-s[0]);
			pivotGausselimination(tmp, egin_vec, b); 
			printf("( ");
			for (int j = 0; j < 10; j++) {
				printf("%.12e ", egin_vec[j]);
			}
			printf(")\n\n");
			delete tmp;
		}	
	}
	system("pause");
	return 0;
}


void pivotGausselimination(numeric::SquareMatrix<double>* A, double ans[], double b[]) {
	int dim = A->getDim();
	//消元
	for (int k = 0; k < dim - 1; k++) {
		int max_index = k;
		for (int i = k; i < dim; i++) {//max i
			if ( fabs(A->get(i, k)) > fabs(A->get(max_index, k)) ) {
				max_index = i;
			}
		}

		for (int j = k; j < dim; j++) {//swap
			double tmp = A->get(k,j);
			A->set(k, j, A->get(max_index, j) );
			A->set(max_index, j, tmp);
		}
		double tmp = b[k];
		b[k] = b[max_index];
		b[max_index] = tmp;
		double m=0.0;
		for (int t = k + 1; t < dim; t++) {
			m = A->get(t, k) / A->get(k, k);
			
			for (int p = k + 1; p < dim; p++) {
				double val = A->get(t, p) - m*A->get(k, p);
				A->set(t, p,  val);
			}

			b[t] = b[t] - m*b[k];
		}
	}
	//回代
	if (fabs(A->get(dim-1, dim-1)) < 1e-12) {
		ans[dim-1] = 1.0;
	}else {
		ans[dim - 1] = b[dim-1] / A->get(dim - 1, dim - 1);
	}
	
	for (int k = dim - 2; k >= 0; k--) {
		double sum = 0.0;
		for (int j = k + 1; j < dim; j++) {
			sum = sum + A->get(k, j) * ans[j];
		}
		if (fabs(A->get(k, k)) < 1e-12) {
			ans[k] = 1.0;
		}
		else {
			ans[k] = (b[k] - sum) / A->get(k, k);
		}
	}
}
