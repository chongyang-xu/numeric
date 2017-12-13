#ifndef NUMERIC_DENSE_MATRIX_H
#define NUMERIC_DENSE_MATRIX_H
#include"squarematrix.h"
#include "vectorutil.h"
#include"matrix.h"
#include<cstdio>
#include<algorithm>

namespace numeric {

template<class T> class Matrix;

template<class T>
class DenseMatrix : public SquareMatrix<T> {
public:
	/*
		Warning!
		logic for lu_decomposed_mat not finished
		when set(i,j,val),should release lu_decomposed_mat
	*/
	explicit DenseMatrix(int n) :dim(n),lu_decomposed_mat(NULL) {
		data = new T*[n];
		for (int i = 0; i < n; i++) {
			data[i] = new T[n];
			memset(data[i], 0, sizeof(T)*dim);
		}
	}
	explicit DenseMatrix(const DenseMatrix& other){
		dim = other.dim;
		lu_decomposed_mat = NULL;
		data = new T*[dim];
		for (int i = 0; i < dim; i++) {
			data[i] = new T[dim];
			memcpy(data[i], other.data[i], sizeof(T)*dim);
		}
	}
	explicit DenseMatrix(Matrix<T>& other) {
		if (other.getCol() != other.getLine()) {
			printf("Cant convert non-aquare matrix to DenseMatrix! %s : %d\n", __FILE__, __LINE__);
			throw;
		}
		lu_decomposed_mat = NULL;
		dim = other.getCol();
		data = new T*[dim];
		for (int i = 0; i < dim; i++) {
			data[i] = new T[dim];
			memcpy(data[i], other.data[i], sizeof(T)*dim);
		}
	}
	~DenseMatrix() {
		for (int i = 0; i<dim; i++) {
			delete[] data[i];
		}
		delete[] data;
		data = NULL;
		if (lu_decomposed_mat) {
			delete lu_decomposed_mat;
			lu_decomposed_mat = NULL; 
		}
	}
	
	virtual  T		get(int i, int j) { return data[i][j]; }
	virtual  void	set(int i, int j, T val) { data[i][j] = val; }
	virtual  int	getDim() { return dim; }
	
	virtual SquareMatrix<T>*  addI(T u)  {
		DenseMatrix<T>* res = new DenseMatrix(*this);
		for (int i = 0; i < dim; i++) {
			res->data[i][i] = this->data[i][i] + u;
		}
		return res;
	}
	virtual SquareMatrix<T>*  subMatrix(SquareMatrix<T>* another, double scale = 1.0) {
		DenseMatrix<T>* res = new DenseMatrix(*this);
		DenseMatrix<T>* tmp = dynamic_cast< DenseMatrix<T>* >(another);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				res->data[i][j] -= scale*tmp->data[i][j];
			}
		}
		return res;
	}
	virtual SquareMatrix<T>*  mulMatrix(SquareMatrix<T>* another, double scale = 1.0) {
		DenseMatrix<T>* res = new DenseMatrix<T>(this->dim);
		DenseMatrix<T>* tmp = dynamic_cast< DenseMatrix<T>* >(another);
		for (int i = 0; i < dim; i++) {
			for (int k = 0; k < dim; k++) {
				for (int j = 0; j < dim; j++) {
					res->data[i][j] += this->data[i][k] * scale * tmp->data[k][j];
				}
			}
		}
		return res;
	}
	virtual SquareMatrix<T>*  getMatrix(int x, int y, int num) {//deep copy
		DenseMatrix<T>* res = new DenseMatrix<T>(num);
		for (int i = 0; i < num; i++) {
			memcpy(res->data[i], data[i+x]+y, sizeof(T)*num);
		}
		return res;
	}
	virtual void			  setMatrix(int x, int y, SquareMatrix<T>* other) {
		DenseMatrix<T>* mat = dynamic_cast<DenseMatrix<T>*>(other);
		for (int i = 0; i < mat->getDim(); i++) {
			memcpy(data[i+x]+y, mat->data[i], sizeof(T)*mat->getDim());
		}
	}

	virtual  SquareMatrix* LUDecompose()  { 
		DenseMatrix* mat = new DenseMatrix(*this);
		for (int k = 0; k < mat->dim; k++) {//k=0,1,2,...,dim-1
			double sigma;
			//Ukj = Akj - sigma(Lkt*Utj)
			for (int j = k; j < mat->dim; j++) {
				sigma = 0.0;
				for (int t = 0; t < k; t++) {
					//sigma += l[k][t] * u[t][j];
					sigma += mat->get(k, t) * mat->get(t, j);
				}
				//u[k][j] = a[k][j] - sigma;
				mat->set(k, j, mat->get(k, j) - sigma);
			}
			//Lik = (Aik - sigma(Lit*Utk) )/Ukk
			if (k < mat->dim - 1) {
				for (int i = k + 1; i < mat->dim; i++) {
					sigma = 0.;
					for (int t = 0; t < k; t++) {
						//sigma += l[i][t] * u[t][k];
						sigma += mat->get(i, t) * mat->get(t, k);
					}
					//l[i][k] = (a[i][k] - sigma)/u[k][k];
					mat->set(i, k, (mat->get(i, k) - sigma) / mat->get(k, k) );
				}
			}
			

		}
		return mat;
	}
	virtual  SquareMatrix* QRDecompose()  { throw; }
	virtual  SquareMatrix* QuasiUpperTriangularize()  { 
		DenseMatrix* quasi = new DenseMatrix(*this);
		bool a_i_r_all_zero;
		double d, c, h;
		
		int quasi_dim = quasi->dim;
		T* u = new T[quasi_dim];
		T* p = new T[quasi_dim];
		T* q = new T[quasi_dim];
		double t;
		T* w = new T[quasi_dim];
		
		for (int r = 0; r < quasi_dim - 2; r++) {
			//step1
			{
				a_i_r_all_zero = true;
				for (int i = r + 2; i < quasi_dim; i++) {
					if (fabs(quasi->data[i][r]) > 1e-12) {
						a_i_r_all_zero = false;
						break;
					}
				}
				if (a_i_r_all_zero) {
					continue;
				}
			}
			//step2
			{
				d = c = h = 0.0;
				for (int i = r + 1; i < quasi_dim; i++) {
					d = d + (quasi->data[i][r] * quasi->data[i][r]);
				}
				d = sqrt(d);
				c = d*(quasi->data[r + 1][r] > 0.0 ? -1 : 1);//data[r+1][r]==0 => c = d;
				h = c*c - c * quasi->data[r + 1][r];

			}
			//step3
			{
				for (int i = 0; i < r + 1; i++) { u[i] = 0.0; }
				u[r + 1] = quasi->data[r + 1][r] - c;
				for (int i = r+2; i < quasi_dim; i++) { u[i] = quasi->data[i][r]; }
			}
			//step4
			{
				t = 0.0;
				quasi->transMulVec(u, p);//p = qusai*u 
				VectorUtil<T>::vecScale(p, 1.0/h, quasi_dim);//p=p/h
				quasi->mulVec(u, q);//q = qusai*u 
				VectorUtil<T>::vecScale(q, 1.0/h, quasi_dim);//p = q/h
				t = VectorUtil<T>::innerProduct(p, u, quasi_dim) / h;
				for (int i = 0; i < quasi_dim; i++) {//w = q-t*u
					w[i] = q[i] - t*u[i];
				}
				SquareMatrix<T>*a = VectorUtil<T>::aMulTransB(w,u, quasi_dim);
				SquareMatrix<T>*b = VectorUtil<T>::aMulTransB(u, p, quasi_dim);
				SquareMatrix<T>*c = quasi->subMatrix(a);
				SquareMatrix<T>*d = c->subMatrix(b);
				delete quasi;
				quasi = dynamic_cast<DenseMatrix* >(d);
				d = NULL;
				delete a;
				delete b;
				delete c;
			}
		}//end for

		delete[] u;
		delete[] p;
		delete[] q;
		delete[] w;
		
		return quasi;
	}
	virtual  void solveEquation(T b[], T x[])   { 
		DenseMatrix* mat = NULL;
		if (lu_decomposed_mat) {
			mat = lu_decomposed_mat;		}
		else {
			lu_decomposed_mat = dynamic_cast<DenseMatrix*>(this->LUDecompose());
			mat = lu_decomposed_mat;
		}
		
		//decomposed matrix has same dim,width,...	
		//solve Ax=b
		T* y = new T[dim];
		memset(y, 0, sizeof(T)*dim);
		double sigma;
		//Ly=b
		y[0] = b[0] ;
		for (int i = 1; i < dim; i++) {
			sigma = 0.0;
			for (int t = 0; t < i; t++) {
				sigma += mat->get(i, t)*y[t];
			}
			y[i] = b[i] - sigma;
		}
		//Ux=y

		x[dim - 1] = y[dim - 1] / mat->get(dim - 1, dim - 1);
	/*	if (fabs(mat->get(dim - 1, dim - 1)) < 1e-12) {
			x[dim - 1] = 1.0;
		}
		else {
			x[dim - 1] = y[dim - 1] / mat->get(dim - 1, dim - 1);
		}
	*/
		
		for (int i = dim - 2; i >= 0; i--) {
			sigma = 0.0;
			for (int t = i + 1; t < dim; t++) {
				sigma += mat->get(i, t)*x[t];
			}
			x[i] = (y[i] - sigma) / mat->get(i, i);
/*			if (fabs(mat->get(i, i)) < 1e-12) {
				x[i] = 1.0;
			}
			else {
				x[i] = (y[i] - sigma) / mat->get(i, i);
			}
*/
			}

		delete[] y;
	}

	virtual  void	printRawData() {
		printf("RawData...\n");
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				printf("%.12e\t ", get(i, j));
			}
			printf("\n\n");
		}
	}
	virtual  void	printMatrix()  {
		printf("Matrix...\n");
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				printf("%+.12e\t ", get(i, j));
			}
			printf("\n\n");
		}
	}
private:
	T** data;
	int dim;
	DenseMatrix* lu_decomposed_mat=NULL;
};

}

#endif
