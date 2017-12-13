#include"squarematrix.h"
#include"densematrix.h"
#include<iostream>

int maindfsd() {
	numeric::SquareMatrix<double>* m = new numeric::DenseMatrix<double>(3);
	double ans[5];
	double y[5] = { 1. , 0, 0 ,0, 0};

	m->set(0, 0, 26); m->set(0, 1, 32); m->set(0, 2, 38);// m->set(0, 3, 0); m->set(0, 4, 0);
	m->set(1, 0, 32); m->set(1, 1, 40); m->set(1, 2, 48);// m->set(1, 3, 0); m->set(0, 4, 0);
	m->set(2, 0, 38); m->set(2, 1,48);  m->set(2, 2, 58);// m->set(2, 3, 1); m->set(0, 4, 0);
	//m->set(3, 0, 0); m->set(3, 1, 0); m->set(3, 2, 1);// m->set(3, 3, 7); m->set(3, 4, 1);
	//m->set(4, 0, 0); m->set(4, 1, 0); m->set(4, 2, 0);// m->set(4, 3, 1); m->set(4, 4, 8);
	m->printMatrix();
	m->solveEquation(y, ans);
	for (int i = 0; i < 5; i++)printf("%lf\n", ans[i]);
	//delete m;
	//delete res;
/*
	m->set(0, 0, 2); m->set(0, 1, 1); m->set(0, 2, 3); m->set(0, 3, 4); 
	m->set(1, 0, 1); m->set(1, 1,-1); m->set(1, 2, 2); m->set(1, 3, 1);
	m->set(2, 0, -1);m->set(2, 1, 2); m->set(2, 2, 1); m->set(2, 3, 2);
	m->set(3, 0, 1); m->set(3, 1, 0); m->set(3, 2, -1); m->set(3, 3, 3);


	m->set(0, 0, 1); m->set(0, 1, 3); m->set(0, 2, 5); m->set(0, 3, 7);
	m->set(1, 0, 2); m->set(1, 1, 4); m->set(1, 2, 6); m->set(1, 3, 8);
	m->set(2, 0, 11); m->set(2, 1, 22); m->set(2, 2, 3); m->set(2, 3, 44);
	m->set(3, 0, 55); m->set(3, 1, 44); m->set(3, 2, 33); m->set(3, 3, 22);
	*/
	/*
	m->get(1, 2);
	m->printMatrix();
	m->printRawData();
	m->mulVec(y,ans);
	printf("%lf,%lf,%lf\n", ans[0], ans[1], ans[2]);
	m->transMulVec(y, ans);
	printf("%lf,%lf,%lf\n", ans[0], ans[1], ans[2]);
*/
	/*
	printf("Input:\n");
	m->printMatrix();
	numeric::SquareMatrix<double>* n =  m->QuasiUpperTriangularize();
	n->printMatrix();
	*/
//	m->solveEquation(y, ans);
//	for (int i = 0; i < 4; i++) {
//		printf("%lf\n", ans[i]);
//	}
/*
	numeric::SquareMatrix<double>* n = m->mulMatrix(m);
	n->printMatrix();
	delete n;
	n = m->getMatrix(0,0,2);
	printf("N:\n");
	n->printMatrix();
	printf("M before set:\n");
	m->printMatrix();
	m->setMatrix(2,2,n);
	printf("M after set:\n");
	m->printMatrix();
	delete n;
*/
	delete m;
	system("pause");
	return 0;
}