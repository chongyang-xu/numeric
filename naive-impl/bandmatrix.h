#ifndef  NUMERIC_BAND_MATRIX_H
#define  NUMERIC_BAND_MATRIX_H
#include<cstring>
#include<cstdio>
#include<algorithm>
#include "squarematrix.h"

namespace numeric {

template<class T>
class BandMatrix : public SquareMatrix<T> {
public:
	BandMatrix(int dimension, int lower_width, int upper_width) :dim(dimension), low_width(lower_width), up_width(upper_width), decomposed_matrix(NULL){
		width = low_width + up_width + 1;
		data = new T*[width];
		for (int i = 0; i<width; i++) {
				data[i] = new T[dim];
				memset(data[i], 0, sizeof(T)*dim);
		}
	}
	explicit BandMatrix(const BandMatrix& other):dim(other.dim), low_width(other.low_width), up_width(other.up_width) {
		width = other.width;
		decomposed_matrix = NULL;//set to NULL to avoid mistakes
		data = new T*[width];
		for (int i = 0; i<width; i++) {
			data[i] = new T[other.dim];
			memcpy(data[i], other.data[i], sizeof(T)*dim);
		}
	}
	~BandMatrix() {
		for (int i = 0; i<width; i++) {
			delete[] data[i];
		}
		delete[] data;
		data = NULL;
		if (decomposed_matrix) delete decomposed_matrix;
		decomposed_matrix = NULL;
	}
	
	virtual  T get(int i, int j)   {
		if ((j <= i + up_width) && (j >= i - low_width)) {
			return data[i - j + up_width][j];
		}
		return 0.0;
		
	}
	virtual void set(int i, int j, T val) {
		//notes for speed, or not notes for safety
		if ((j <= i + up_width) && (j >= i - low_width)) {
			data[i - j + up_width][j] = val;
		}
	}
	virtual int getDim()   { return dim; }

	virtual SquareMatrix<T>* LUDecompose()  {
		BandMatrix* mat =  DoolittleDecompose();
		return mat;
	}
	virtual SquareMatrix<T>* QRDecompose()  { throw; }
	virtual SquareMatrix<T>* QuasiUpperTriangularize()  { throw; }
	virtual void solveEquation(T b[], T x[]) {
		
		if (decomposed_matrix == NULL) {
			decomposed_matrix = DoolittleDecompose();
		}
		//decomposed matrix has smae dim,width,...	
		//solve Ax=b
		T* y = new T[dim];
		memset(y, 0, sizeof(T)*dim);
		double sigma;
		int start_index;
		int end_index;

		//Ly=b
		y[0] = b[0];
		for (int i = 1; i < dim; i++) {
			sigma = 0.0;
			start_index = std::max<int>(0, i - low_width);
			for (int t = start_index; t < i; t++) {
				sigma += decomposed_matrix->get(i, t)*y[t];
			}
			y[i] = b[i] - sigma;
		}

		//Ux=y
		x[dim - 1] = y[dim - 1] / decomposed_matrix->get(dim - 1, dim - 1);
		for (int i = dim - 2; i >= 0; i--) {
			sigma = 0.0;
			end_index = std::min<int>(i + up_width +/**/1, dim);
			for (int t = i + 1; t < end_index; t++) {
				sigma += decomposed_matrix->get(i, t)*x[t];
			}
			x[i] = (y[i] - sigma) / decomposed_matrix->get(i, i);
		}

		delete[] y;
	}

	virtual SquareMatrix<T>*	addI(T u)  {
		BandMatrix* mat = new BandMatrix(*this);
		mat = new BandMatrix(dim, low_width, up_width);
		for (int i = 0; i < width; i++) {
			if (i != up_width) {
				memcpy(mat->data[i], data[i], sizeof(T)*dim);
			}
			else {
				for (int j = 0; j < dim; j++) {
					mat->data[up_width][j] = data[up_width][j] + u;
				}
			}
		}
		return mat;
	}
	virtual void			mulVec(T b[],T ans[])   {
		memset(ans, 0, sizeof(T)*dim);
		for (int i = 0; i < dim; i++) {
			int start = std::max<int>(0, i-low_width);
			int end = std::min<int>(dim, i+up_width);
			for (int j  = start;  j<=end; j++){
				ans[i] += get(i, j)*b[j];
			}
		}
	}
	virtual double			det()   {
		BandMatrix<T>*mat = DoolittleDecompose();
		double res = 1.0;
		for (int i = 0; i < mat->dim; i++) {
			res *= mat->data[mat->up_width][i];
		}
		delete mat;
		return res;
	}
	
	virtual SquareMatrix<T>*   subMatrix(SquareMatrix<T>* another, double scale = 1.0) { throw; }
	virtual SquareMatrix<T>*   mulMatrix(SquareMatrix<T>* another, double scale = 1.0) { throw; }
	virtual SquareMatrix<T>*   getMatrix(int x, int y, int num) { throw; }
	virtual void			   setMatrix(int x, int y, SquareMatrix<T>* other) { throw; }

	virtual void printMatrix()  {
		printf("========================================\n");
		printf("Matrix...\n");
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				printf("%lf ", get(i, j));
			}
			printf("\n");
		}
		printf("========================================\n");
	}
	virtual void printRawData()  {
		printf("========================================\n");
		printf("Raw Data...\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < dim; j++) {
				printf("%lf ", data[i][j]);
			}
			printf("\n");
		}
		printf("========================================\n");
		
	}
	void printArrayX(double* arr,int dim) {
		printf("========================================\n");
		printf("double X[%d]...\n",dim);
		for (int i = 0; i < dim; i++) { printf("x[%d] = %lf\n", i, arr[i]); }
		printf("========================================\n");
	}

	//just used for homework
	void initializeForHomework(int dimension, int lower_width, int upper_width) {
		for (int i = 0; i < 501; i++) data[0][i] = -0.064;
		for (int i = 0; i < 501; i++) data[1][i] = 0.16;
		for (int i = 0; i < 501; i++) 
			data[2][i] = (1.64-0.024*(i+1.0))*sin(0.2*(i+1.0)) - 0.64*exp(0.1/(i+1.0));
		for (int i = 0; i < 501; i++) data[3][i] = 0.16;
		for (int i = 0; i < 501; i++) data[4][i] = -0.064;
	}
private:
	int dim;
	int low_width;
	int up_width;
	int width;
	T** data;
	BandMatrix* decomposed_matrix;

	BandMatrix* DoolittleDecompose()  {
		BandMatrix* mat = new BandMatrix(*this);
		for (int k = 0; k < mat->dim; k++) {//k=0,1,2,...,dim-1
			double sigma;
			int inner_start_index;
			int outter_end_index;
			int max1 = std::max<int>(0, k - mat->low_width);
			int max2 = std::max<int>(0, k - mat->up_width);

			//Ukj = Akj - sigma(Lkt*Utj)
			outter_end_index = std::min<int>(k + mat->up_width, mat->dim);
			for (int j = k; j < outter_end_index; j++) {
				sigma = 0.0;
				inner_start_index = std::max<int>(max1, j - mat->up_width);
				for (int t = inner_start_index; t <k; t++) {
					//sigma += l[k][t] * u[t][j];
					sigma += mat->get(k, t) * mat->get(t, j);
				}
				//u[k][j] = a[k][j] - sigma;
				mat->set(k, j, mat->get(k, j) - sigma);
			}
			//Lik = (Aik - sigma(Lit*Utk) )/Ukk
			outter_end_index = std::min<int>(k + mat->low_width +/**/1, mat->dim);
			for (int i = k + 1; i < outter_end_index && k<(mat->dim - 1); i++) {
				sigma = 0.;
				inner_start_index = std::max<int>(max2, i - mat->low_width);
				for (int t = inner_start_index; t < k; t++) {
					//sigma += l[i][t] * u[t][k];
					sigma += mat->get(i, t) * mat->get(t, k);
				}
				//l[i][k] = (a[i][k] - sigma)/u[k][k];
				mat->set(i, k, (mat->get(i, k) - sigma) / mat->get(k, k));
			}

		}

		return mat;
	}

};

}
#endif
