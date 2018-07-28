#ifndef  NUMERIC_ENGINE_SOLVER_H
#define  NUMERIC_ENGINE_SOLVER_H
#include"squarematrix.h"
#include"bandmatrix.h"
#include"vectorutil.h"
#include<assert.h>
#include <complex>  

namespace numeric {

template<class T>
class EigenSolver{
public:	
	explicit EigenSolver(SquareMatrix<T> * mat, double epsi = 1e-12, int max_iter_num=1e6) :matrix(mat), epison(epsi), max_iter(max_iter_num) {}

	SquareMatrix<T>* QRMethod(std::complex<T> engin[]) {
		SquareMatrix<T> * quasi = matrix->QuasiUpperTriangularize();
		int k = 0;
		int m = quasi->getDim();
		while (true) {
			if (fabs(quasi->get(m - 1, m - 2)) <= epison) {
				engin[m - 1] = std::complex<T>(quasi->get(m - 1, m - 1), 0.0);
				m--;
				step4:
					if (m == 1) {
						engin[0] = std::complex<T>(quasi->get(0, 0), 0.0);
						break;
					}
					else if (m == 0) {break;	}
					else/* m>1 */ {continue;}
			}
			double s, t;
			{//step5,6,7
				s = quasi->get(m - 1, m - 1) + quasi->get(m - 2, m - 2);
				t = quasi->get(m - 1, m - 1)*quasi->get(m - 2, m - 2) - quasi->get(m - 1, m - 2)*quasi->get(m - 2, m - 1);
				//x^2 - s*x + t = 0;
				std::complex<T> s1, s2;
				double delta = s*s - 4 * t;
				if (delta < 0) {
					s1 = std::complex<T>(s / 2, -sqrt(-delta) / 2);
					s2 = std::complex<T>(s / 2, sqrt(-delta) / 2);
				}
				else {
					s1 = std::complex<T>((s - sqrt(delta)) / 2, 0);
					s2 = std::complex<T>((s + sqrt(delta)) / 2, 0);
				}
				//step6
				if (m == 2) {
					engin[0] = s1;
					engin[1] = s2;
					break;
				}
				//step7
				if (fabs(quasi->get(m - 2, m - 3)) <= epison) {
					engin[m - 1] = s2;
					engin[m - 2] = s1;
					m -= 2;
					goto step4;
				}
			}
			{//step8
				if (k == max_iter) {
					printf("dont get all engin\n");
					break;
				}
			}
			{//step9:
				SquareMatrix<T> * A = quasi->getMatrix(0, 0, m);//deep copy
				SquareMatrix<T> * matrix_m = A->mulMatrix(A);
				SquareMatrix<T> * matrix_m2 = matrix_m->subMatrix(A, s);
				SquareMatrix<T> * Mk = matrix_m2->addI(t);
				delete matrix_m;
				delete matrix_m2;

				bool a_i_r_all_zero;
				double d, c, h;

				int b_c_dim = Mk->getDim();
				assert(b_c_dim == m);
				T* u = new T[b_c_dim];
				T* v = new T[b_c_dim];
				T* p = new T[b_c_dim];
				T* q = new T[b_c_dim];
				double t;
				T* w = new T[b_c_dim];

				for (int r = 0; r < b_c_dim -1 ; r++) {
					//step1
					{
						a_i_r_all_zero = true;
						for (int i = r + 1; i < b_c_dim; i++) {
							if (fabs(Mk->get(i, r)) > 1e-12) {
								a_i_r_all_zero = false;
								break;
							}
						}
						if (a_i_r_all_zero) {continue;}
					}
					//step2
					{
						d = c = h = 0.0;
						for (int i = r; i < b_c_dim; i++) {
							d = d + (Mk->get(i, r) * Mk->get(i, r));
						}
						d = sqrt(d);
						c = d*(Mk->get(r, r) > 0.0 ? -1 : 1);
						h = c*c - c * Mk->get(r, r);
					}
					//step3
					{
						for (int i = 0; i < r; i++) { u[i] = 0.0; }
						u[r] = Mk->get(r, r) - c;
						for (int i = r + 1; i < b_c_dim; i++) { u[i] = Mk->get(i, r); }
					}
					//step4
					{
						t = 0.0;
						Mk->transMulVec(u, v);
						VectorUtil<T>::vecScale(v, 1.0 / h, b_c_dim);

						SquareMatrix<T>* uv_T = VectorUtil<T>::aMulTransB(u, v, b_c_dim);
						SquareMatrix<T>* res = Mk->subMatrix(uv_T);
						delete Mk;
						delete uv_T;
						Mk = res;
						res = NULL;

						A->transMulVec(u, p);
						VectorUtil<T>::vecScale(p, 1.0 / h, b_c_dim);//p=p/h
						A->mulVec(u, q);//q = qusai*u 
						VectorUtil<T>::vecScale(q, 1.0 / h, b_c_dim);//p = q/h
						t = VectorUtil<T>::innerProduct(p, u, b_c_dim) / h;
						for (int i = 0; i < b_c_dim; i++) {//w = q-t*u
							w[i] = q[i] - t*u[i];
						}

						SquareMatrix<T>*a = VectorUtil<T>::aMulTransB(w, u, b_c_dim);
						SquareMatrix<T>*b = VectorUtil<T>::aMulTransB(u, p, b_c_dim);
						SquareMatrix<T>*c = A->subMatrix(a);
						SquareMatrix<T>*d = c->subMatrix(b);
						delete A;
						A = d;
						d = NULL;
						delete a; a = NULL;
						delete b; b = NULL;
						delete c; c = NULL;
					}//end step4
				}//end for
				quasi->setMatrix(0, 0, A);
				delete Mk;
				delete A;
				delete[] u;
				delete[] v;
				delete[] p;
				delete[] q;
				delete[] w;
			}//end step 9
			k++;//step10
		}//end while
		return quasi;
	}

	double getNormMaxEigen(T y[], double offset){
		int dim = matrix->getDim();
		T* u = new T[dim];
		for (int i = 0; i < dim; i++) u[i] = 1.0;

		double yita = 0.0;
		double beta = 0.0;
		double beta1 = 10.0;
		bool converged = false;
		SquareMatrix<T>* mat = matrix->addI(-1*offset);
		
		while (!converged) {
			beta = beta1;
			yita = VectorUtil<T>::squareNorm(u, dim);
			for (int i = 0; i < dim; i++) {
				y[i] = u[i] / yita;//vec = u / norm(u)
			}
			//u = mat * vec
			mat->mulVec(y, u);
			//beta = vec^T * u
			beta1 = VectorUtil<T>::innerProduct(y, u, dim);
			
			if (fabs( (beta1 - beta) / beta1) <= epison) {
				converged = true;
			}
		}
		delete[] u;
		delete mat;
		return (beta1);

	}

	double getNormMinEigen(T vec[], double offset){
		int dim = matrix->getDim();
		T* u = new T[dim];
		for (int i = 0; i < dim; i++) u[i] = 1.0;

		double yita = 0.0;
		double beta = 0.0;
		double beta1 = 10.0;
		bool converged = false;

		SquareMatrix<T>* mat = matrix->addI(-1*offset);
		while (!converged) {
			beta = beta1;
			//vec = u / norm(u)
			yita = VectorUtil<T>::squareNorm(u,dim);
			for (int i = 0; i < dim; i++) {
				vec[i] = u[i] / yita;
			}
			//mat * u =  vec => u
			mat->solveEquation(vec, u);
			//beta = vec^T * u
			beta1 = VectorUtil<T>::innerProduct(vec, u, dim);

			if (fabs((1.0/beta1 - 1.0/beta) / (1.0/beta1)) <= epison) {
				converged = true;
			}
		}
		delete[] u;
		delete mat;
		return (1.0/beta1);
	}
	
	void setMatrix(SquareMatrix<T> * other) {
		matrix = other;
	}
	void setAccuracy(double epsi) {
		epison = epsi;
	}
	
private:
	SquareMatrix<T> * matrix;
	double epison;
	int max_iter;
};

}
#endif