#ifndef  NUMERIC_MISCELLANEOUS_H
#define  NUMERIC_MISCELLANEOUS_H

#include"vectorutil.h"
#include"polynomial.h"
#include"numbertable.h"
#include"densematrix.h"

namespace numeric {

/*
x=G(x)
||G(x)-G(y)||<=L||x-y|| , L in (0,1)
*/
template<class T>
bool FixedPointIteration(int num_unkonw, T ans[], T(*iter_vec[])(T*,int), double epson = 1e-12) {
	static int max_iter = 2 << 16;
	bool  converged = false;
	int  counter = 0;
	T* tmp = new T[num_unkonw];
	while (!converged && counter++ < max_iter)
	{
		for (int i = 0; i < num_unkonw; i++) {
			tmp[i] = ans[i];
			ans[i] = iter_vec[i](ans, num_unkonw);
			printf("ans[%d]=%lf\n",i ,ans[i]);
			tmp[i] = ans[i] - tmp[i];
		}
		double res_norm = VectorUtil<T>::squareNorm(tmp, num_unkonw);
		double ans_norm = VectorUtil<T>::squareNorm(ans, num_unkonw);
		if (res_norm / ans_norm <= epson) {
			converged = true;
		}
	}
	delete[] tmp;
	return converged;
}

typedef  double(*FUNC)(double*, int);

bool NewtonMethodForNonLinearEquation(
	int num_unkonw, 
	double ans[], 
	FUNC* F,
	FUNC** dF,
	int max_iter = 1<<16,
	double epson = 1e-12
) {
	bool  converged = false;
	int	  counter   = 0;
	double*	  delta_x   = new double[num_unkonw];
	double*   neg_Fx   = new double[num_unkonw];
	
	while (!converged && counter++ < max_iter)
	{
		//-F(x)
		for (int i = 0; i < num_unkonw; i++) {
			neg_Fx[i] = -F[i](ans, num_unkonw);
		}
		//must re-allocate every time because of DenseMatrix.set()
		DenseMatrix<double>* dFMatrix = new DenseMatrix<double>(num_unkonw);
		//dF(x)
		for (int i = 0; i < dFMatrix->getDim(); i++) {
			for (int j = 0; j < dFMatrix->getDim(); j++) {
				dFMatrix->set(i, j, dF[i][j](ans, num_unkonw));
			}
		}
		//dF(x)*deta_x=F(x) ==> delta_x
		dFMatrix->solveEquation(neg_Fx, delta_x);
		delete dFMatrix;
		//Xk+1=Xk+deltaX
		for (int i = 0; i < num_unkonw; i++) {
			ans[i] = ans[i] + delta_x[i];
		}

		double delta_x_norm = VectorUtil<double>::squareNorm(delta_x, num_unkonw);
		double ans_norm = VectorUtil<double>::squareNorm(ans, num_unkonw);
		if (delta_x_norm / ans_norm <= epson) {
			converged = true;
		}

		//printf("Counter : \%d\n", counter);
		//for (int i = 0; i < 4; i++)printf("ans[%d] = %lf ", i, ans[i]); printf("\n");
	}
	delete[] delta_x;
	delete[] neg_Fx;
	
	return converged;
}

/*
	To avoid the programming complexity of the  many pieces polynomial expression
	do online interpolation

	(1) query a point (query_x, query_y)
	(2) get the approximate value
		
*/
template<class T>
int getXIndex(NumberTableVar2<T>& num_table, T query_x) {
	int index_i = 0;//index_i-1,index_i,index_i+1 : 3 interpolation point for quer_x
	double h_x = num_table.var1[1] - num_table.var1[0];
	if (query_x <= (num_table.var1[1] + h_x / 2)) {
		index_i = 1;
	}
	else if (query_x > (num_table.var1[num_table.dim1 - 1 - 1] - h_x / 2)) {
		index_i = num_table.dim1 - 1 - 1;
	}
	else {
		for (int i = 2; i <= (num_table.dim1 - 1 - 2); i++) {
			if (query_x > (num_table.var1[i] - h_x / 2) && query_x <= (num_table.var1[i] + h_x / 2))
			{
				index_i = i;
			}
		}
	}
	return index_i;
}

template<class T>
int getYIndex(NumberTableVar2<T>& num_table, T query_y) {
	int index_j = 0;//index_j-1,index_j,index_j+1 : 3 interpolation point for quer_y
	double h_y = num_table.var2[1] - num_table.var2[0];
	if (query_y <= (num_table.var2[1] + h_y / 2)) {
		index_j = 1;
	}
	else if (query_y > (num_table.var2[num_table.dim2 - 1 - 1] - h_y / 2)) {
		index_j = num_table.dim2 - 1 - 1;
	}
	else {
		for (int i = 2; i <= (num_table.dim2 - 1 - 2); i++) {
			if (query_y > (num_table.var2[i] - h_y / 2) && query_y <= (num_table.var2[i] + h_y / 2))
			{
				index_j = i;
			}
		}
	}
	return index_j;
}

template<class T>
double DualQuadraticPiecewiseInterpolation(NumberTableVar2<T>& num_table, T query_x, T query_y) {
		
	int index_i = getXIndex<T>(num_table, query_x);
	int index_j = getYIndex<T>(num_table, query_y);
	//printf("index-i,index_j = %d,%d\n", index_i, index_j);
	double Lx[3];
	double Ly[3];

	for (int k = 0; k < 3; k++) {
		Lx[k] = 1.0;
		for (int i = index_i - 1; i <= index_i + 1; i++) {
			if (i != (index_i - 1 + k)) {
				Lx[k] = Lx[k] * (query_x - num_table.var1[i]) / (num_table.var1[index_i - 1 + k] - num_table.var1[i]);
			}//lagrange interpolation base function
		}
	}

	for (int k = 0; k < 3; k++) {
		Ly[k] = 1.0;
		for (int i = index_j - 1; i <= index_j + 1; i++) {
			if (i != (index_j - 1 + k)) {
				Ly[k] = Ly[k] * (query_y - num_table.var2[i]) / (num_table.var2[index_j - 1 + k] - num_table.var2[i]);
			}
		}
	}
	//for (int i = 0; i < 3; i++)printf("Lx[%d]=%lf ",i,Lx[i]); printf("\n");
	// for (int i = 0; i < 3; i++)printf("Ly[%d]=%lf ",i, Ly[i]); printf("\n");

	double res = 0.0;
	for (int p = 0; p < 3; p++) {
		for (int q = 0; q < 3; q++) {
			res += Lx[p] * Ly[q] * num_table.value->get(index_i - 1 + p, index_j - 1 + q);
		}
	}
	return res;

}
template<class T>
void constructIndependentBase(Var1Polynomial<T>** bases, int base_order, T* point, int point_num) {
	if (base_order > point_num) { throw; }
	for (int i = 0; i <= base_order; i++) {
		//Var1Polinomial<T> a = Var1Polinomial<T>(base_num);
		//bases[i] = a;
		bases[i] = new Var1Polynomial<T>(base_order);
		bases[i]->set(i,1);
	}
}

template<class T>
void constructOrthogonalBase(Var1Polynomial<T>** bases, int base_order, T* point, int point_num) {
	if (base_order > point_num) { throw; }
	bases[0] = new  Var1Polynomial<T>(0);
	bases[0]->set(0,1);
	double sum_up = 0.0;
	for (int i = 0; i < point_num; i++) {
		sum_up += point[i];
	}
	double alpha = sum_up / point_num;
	bases[1] = new  Var1Polynomial<T>(1);
	bases[1]->set(0, -alpha);
	bases[1]->set(1,1.0);
	bases[1]->print();
	for (int j = 1; j < base_order; j++) {
		double sum1 = 0.0;
		double sum2 = 0.0;
		for (int i = 0; i < point_num; i++) {
			double tmp = bases[j]->eval(point[i]);
			tmp = tmp*tmp;
			sum1 += point[i] * tmp;
			sum2 += tmp;
		}
		double sum4 = 0.0;
		for (int i = 0; i < point_num; i++) {
			double tmp = bases[j-1]->eval(point[i]);
			sum4 += tmp*tmp;
		}
		Var1Polynomial<T> x_alpha = Var1Polynomial<T>(1);
		x_alpha.set(0, -sum1/sum2);
		x_alpha.set(1, 1.0);
		Var1Polynomial<T> poly = x_alpha.mulWithSameVar(*bases[j]).addWithSameVar(*bases[j - 1], -sum2/sum4);
		bases[j + 1] = new Var1Polynomial<T>(poly);
	}
}


template<class T>
Var2Polynomial<T> LeastSquareSurfaceFitting(NumberTableVar2<T>& num_table, int k) {
	//k is max_order of base

	Var1Polynomial<T>** indepent_x_base = new Var1Polynomial<T>*[k+1];
	Var1Polynomial<T>** indepent_y_base = new Var1Polynomial<T>*[k+1];
	constructIndependentBase(indepent_x_base,k, num_table.var1, num_table.dim1);
	constructIndependentBase(indepent_y_base,k, num_table.var2, num_table.dim2);
//	constructOrthogonalBase<T>(indepent_x_base, k, num_table.var1, num_table.dim1);
//	constructOrthogonalBase<T>(indepent_y_base, k, num_table.var2, num_table.dim2);

	T**b = new T*[num_table.dim1];
	for (int i = 0; i < num_table.dim1; i++) {
		b[i] = new T[k+1];
	}
	for (int i = 0; i < num_table.dim1; i++) {
		for (int j = 0; j < k + 1; j++) {
			b[i][j] = indepent_x_base[j]->eval(num_table.var1[i]);
		}
	}
	Matrix<T>* B = new Matrix<T>(b, num_table.dim1, k+1);
	T**g = new T*[num_table.dim2];
	for (int i = 0; i < num_table.dim2; i++) {
		g[i] = new T[k + 1];
	}
	for (int i = 0; i < num_table.dim2; i++) {
		for (int j = 0; j < k + 1; j++) {
			g[i][j] = indepent_y_base[j]->eval(num_table.var2[i]);
		}
	}
	Matrix<T>* G = new Matrix<T>(g, num_table.dim2, k + 1);

	Matrix<T>* C = NULL;
	Matrix<T>* U = new Matrix<T>(*num_table.value);

	Matrix<T>* transB = B->trans();
	Matrix<T>* transBB = transB->mul(B);
	Matrix<T>* inverseTransBB = transBB->inverse();

	Matrix<T>* transG = G->trans();
	Matrix<T>* transGG = transG->mul(G);
	Matrix<T>* inverseTransGG = transGG->inverse();
	
	Matrix<T>* tmp1 = inverseTransBB->mul(transB);
	Matrix<T>* tmp2 = tmp1->mul(U);
	Matrix<T>* tmp3 = tmp2->mul(G);
	C = tmp3->mul(inverseTransGG);

	Var2Polynomial<T> res(*C);
	//res.eval(x,y);

	delete B; delete G; delete U; delete C;
	delete transB; delete transBB; delete inverseTransBB;
	delete transG; delete transGG; delete inverseTransGG;
	delete tmp1; delete tmp2; delete tmp3;
	
	for (int i = 0; i < num_table.dim1; i++) {
		delete[] b[i];
	}
	delete[] b;
	
	for (int i = 0; i < num_table.dim2; i++) {
		delete[] g[i];
	}
	delete[] g;

	for (int i = 0; i < k + 1; i++) {
		delete indepent_x_base[i];
		delete indepent_y_base[i];
	}
	delete[] indepent_x_base;
	delete[] indepent_y_base;

	return res;
}

}

#endif
