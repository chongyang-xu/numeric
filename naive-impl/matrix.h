#ifndef NUMERIC_MATRIX_H
#define NUMERIC_MATRIX_H
#include"densematrix.h"
namespace numeric {

template<class T> class DenseMatrix;
template<class T>
class Matrix {
public:
	friend class DenseMatrix<T>;
	Matrix(int line_, int col_):line(line_),col(col_) {
		data = new T*[line_];
		for (int i = 0; i<line_; i++) {
			data[i] = new T[col_];
			memset(data[i], 0, sizeof(T)*col_);
		}
	}
	Matrix(T* data_[], int line_, int col_) :line(line_), col(col_) {
		data = new T*[line_];
		for (int i = 0; i<line_; i++) {
			data[i] = new T[col_];
			memcpy(data[i], data_[i], sizeof(T)*col_);
		}
	}
	explicit Matrix(const Matrix& other) {
		col = other.col;
		line = other.line;
		data = new T*[line];
		for (int i = 0; i < line; i++) {
			data[i] = new T[col];
			memcpy(data[i], other.data[i], sizeof(T)*col);
		}
	}
	Matrix* trans() {
		Matrix* res = new Matrix(col, line);
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < line; j++) {
				res->data[i][j] = data[j][i];
			}
		}
		return res;
	}
	Matrix* mul(Matrix* another) {
		if (col != another->line) {
			printf("Cant A.mul(B) ! %s : %d\n", __FILE__, __LINE__);
			throw;
		}
		Matrix* res = new Matrix(line, another->col);
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < another->col; j++) {
				res->data[i][j] = 0;
				for (int k = 0; k < col; k++) {
					res->data[i][j] += this->data[i][k] * another->data[k][j];
				}
			}
		}
		return res;
	}
	Matrix* inverse() {
		if (line != col) { 
			printf("only square matrix has inverse! %s : %d\n",__FILE__,__LINE__);
			throw;
		}
		//if det=0 throw
		T** res=new T*[line];
		for (int i = 0; i < line; i++) {
			res[i] = new T[line];
		}
		//Ax=Ii
		T* e = new T[line];
		DenseMatrix<T>* dense = new DenseMatrix<T>(*this);
		for (int i = 0; i < line; i++) {
			memset(e, 0, sizeof(T)*line);
			e[i] = 1;
			dense->solveEquation(e, res[i]);
		}
		delete dense;
		delete[] e;

		Matrix* tmp = new Matrix(res, line, line);
		Matrix* inverse = tmp->trans();
		
		delete tmp;
		for (int i = 0; i < line; i++) {
			delete[] res[i];
		}
		delete[] res;

		return inverse;
	}
	~Matrix(){
		for (int i = 0; i<line; i++) {
			delete[] data[i];
		}
		delete data;
	}
	inline T get(int i, int j) {
		return data[i][j];
	}
	inline void set(int i, int j, T val) {
		data[i][j] = val;
	}
	inline int getLine() { return line; }
	inline int getCol() { return col; }
	void	printMatrix() {
		printf("Matrix...\n");
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < col; j++) {
				printf("%+.12e\t ", get(i, j));
				//printf("%lf\t ", get(i, j));
			}
			printf("\n\n");
		}
	}
private:
	int line;
	int col;
	T** data;
};

}
#endif
