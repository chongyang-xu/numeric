#ifndef NUMERIC_POLINOMIAL_H
#define NUMERIC_POLINOMIAL_H
#include<cstring>
#include"matrix.h"
namespace numeric {

template<class T>
class Var1Polynomial {
public:
	Var1Polynomial() {
		max_order = 0;
		coefficient = new double[max_order + 1];
		memset(coefficient, 0, sizeof(double)*(max_order + 1));
	}
	explicit Var1Polynomial(int order) {
		max_order = order;
		coefficient = new double[max_order+1];
		memset(coefficient, 0, sizeof(double)*(max_order + 1));
	}
	 Var1Polynomial(const Var1Polynomial& other) {
		max_order = other.max_order;
		coefficient = new double[max_order + 1];
		memcpy(coefficient, other.coefficient, sizeof(T)*(max_order + 1));
	}
	Var1Polynomial mulWithSameVar(const Var1Polynomial& other){
		//if (max_order != other.max_order) { throw; }//only compute with same max_order for now
		Var1Polynomial res(max_order+other.max_order);
		for (int i = 0; i <= other.max_order; i++) {
			for (int j = 0; j <= max_order; j++) {
				res.coefficient[i + j] += other.coefficient[i] * this->coefficient[j];
			}
		}
		return res;
	}
	Var1Polynomial addWithSameVar(const Var1Polynomial& other, double scale=1.0) {
		int bigger  = 0.0;
		int smaller = 0.0;
		Var1Polynomial* res = NULL;
		if (other.max_order > max_order) {
			res = new Var1Polynomial(other);
			for (int i = 0; i < max_order + 1; i++) {
				res->coefficient[i] = this->coefficient[i] + other.coefficient[i] * scale;
			}
			for (int i = max_order + 1; i < other.max_order + 1; i++) {
				res->coefficient[i] =  other.coefficient[i] * scale;
			}
		}
		else {
			res = new Var1Polynomial(*this);
			for (int i = 0; i < other.max_order + 1; i++) {
				res->coefficient[i] = this->coefficient[i] + other.coefficient[i] * scale;
			}
			for (int i = other.max_order + 1; i < max_order + 1; i++) {
				res->coefficient[i] = coefficient[i];
			}
		}
		return *res;
	}

	~Var1Polynomial() {
		delete[] coefficient;
		coefficient = NULL;
	}
	void set(int i, double coe) {
		coefficient[i] = coe;
	}
	double eval(T val) {
		double res=0.0;
		double pow_val = 1;
		for (int i = 0; i <= max_order; i++) {
			res += coefficient[i] * pow_val;
			pow_val *= val;
		}
		return res;
	}
	void print() {
		printf("Polinomial : \n");
		printf("\t%+lf", coefficient[0]);
		for (int i = 1; i <= max_order; i++) {
			printf("\t%+lf*x^%d", coefficient[i], i);
		}
		printf("\n");
	}
private:
	double* coefficient;
	int max_order;
};

template<class T>
class Var2Polynomial {
public:
	Var2Polynomial(int order1, int order2) {
		var1_order = order1;
		var2_order = order2;
		coefficient = new Matrix<double>(var1_order + 1, var2_order + 1);
	}
	Var2Polynomial(const Var2Polynomial& other) {
		var1_order = other.var1_order;
		var2_order = other.var2_order;
		coefficient = new Matrix<double>(*other.coefficient);
	}
	explicit Var2Polynomial(Matrix<double>& mat) {
		var1_order = mat.getLine() - 1;
		var2_order = mat.getCol() - 1;
		coefficient = new Matrix<double>(mat);
	}

	~Var2Polynomial() {
		delete coefficient;
	}
	void set(int i, int j, double coe) {
		coefficient->set(i,j,coe);
	}
	double eval(T val1, T val2) {
		double res=0;
		double pow_x = 1.0;
		for (int i = 0; i <= var1_order; i++) {
			double pow_y = 1.0;
			for (int j = 0; j <= var2_order; j++) {
				res += coefficient->get(i,j) * pow_x*pow_y;
				pow_y *= val2;
			}
			pow_x *= val1;
		}
		return res;
	}
	void print() {
		printf("Polinomial : \n");
			for (int i = 0; i <= var1_order; i++) {
				for (int j = 0; j <= var2_order; j++) {
					printf("%+.12e*x^%dy^%d\t", coefficient->get(i,j), i,j);
				}
				printf("\n");
			}
		printf("\n");
	}
private:
	Matrix<double>* coefficient;
	int var1_order;
	int var2_order;
};

}
#endif // NUMERIC_POLINOMIAL_H