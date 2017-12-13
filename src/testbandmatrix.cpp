#include"bandmatrix.h"
#include"eigensolver.h"
#include<iostream>
using namespace std;
int maintest() {
	/*
	A
	4 1 0 0 0
	1 4 1 0 0
	0 1 4 1 0
	0 0 1 4 1
	0 0 0 1 4
	b 
	1.0, 0.5, -1.0, 3.0, 2
	*/
	numeric::BandMatrix<double> m(5, 1, 1);
	m.set(0, 0, 4.0); m.set(0, 1, 1.0);
	m.set(1, 0, 1.0); m.set(1, 1, 4.0); m.set(1, 2, 1.0);
	m.set(2, 1, 1.0); m.set(2, 2, 4.0); m.set(2, 3, 1.0);
	m.set(3, 2, 1.0); m.set(3, 3, 4.0); m.set(3, 4, 1.0);
	m.set(4, 3, 1.0);	m.set(4, 4, 4.0);
	
	double b[5] = { 1.0, 0.5, -1.0, 3.0, 2.0 };
	double X[5] = { 1,2,3,4,5 };

	//m.printRawData();
	m.printMatrix();
	m.solveEquation(b,X);
	m.printArrayX(X,5);
	m.printMatrix();
	system("pause");
	return 0;
}