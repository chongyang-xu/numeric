#include"bandmatrix.h"
#include"eigensolver.h"
#include<cstdio>

int homework1() {
	numeric::BandMatrix<double> A(501,2,2);
	A.initializeForHomework(501, 2, 2);
	double engineVector[501];
	numeric::EigenSolver<double> solver(&A, 1e-12);

	printf("===============Prob1==================\n");
	double lambada_s, lambada_1, lambada_501;
	lambada_s = solver.getNormMinEigen(engineVector, 0.0);
	double res2 = solver.getNormMaxEigen(engineVector,0.0);
	if (res2 < 0) {
		lambada_1 = res2;
		lambada_501 = res2 + solver.getNormMaxEigen(engineVector, res2);
	}else {
		lambada_501 = res2;
		lambada_1 = res2 + solver.getNormMaxEigen(engineVector, res2);
	}
	printf("lambada-1 \t= %.12e\n", lambada_1);
	printf("lambada-501 \t= %.12e\n", lambada_501);
	printf("lambada-s \t= %.12e\n", lambada_s);

	printf("===============Prob2==================\n");
	double Uk = 0.0;
	for (int k = 1; k < 40; k++) {
		Uk = lambada_1 + k*(lambada_501 - lambada_1) / 40.0 ;
		Uk = Uk+solver.getNormMinEigen(engineVector, Uk);
		printf("lambada-i%d \t= %.12e\n",k,Uk);
	}

	printf("===============Prob3==================\n");
	double lambada_max = solver.getNormMaxEigen(engineVector, 0.0);
	printf("cond(A)2 \t= %.12e\n", fabs(lambada_max /lambada_s));
	printf("detA	\t= %.12e\n",A.det());
	system("pause");

	return 0;
}