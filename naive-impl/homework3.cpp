#include"numbertable.h"
#include"miscellaneous.h"
#include"matrix.h"
#include"polynomial.h"

namespace homework3 {
	double global_x=0;
	double global_y=0;
}//global shared in homework3

void initFtu(numeric::NumberTableVar2<double>* table);

double F_0(double* val, int num);
double F_1(double* val, int num);
double F_2(double* val, int num);
double F_3(double* val, int num);

double dF_00(double* val, int num);
double dF_01(double* val, int num);
double dF_02(double* val, int num);
double dF_03(double* val, int num);

double dF_10(double* val, int num);
double dF_11(double* val, int num);
double dF_12(double* val, int num);
double dF_13(double* val, int num);

double dF_20(double* val, int num);
double dF_21(double* val, int num);
double dF_22(double* val, int num);
double dF_23(double* val, int num);

double dF_30(double* val, int num);
double dF_31(double* val, int num);
double dF_32(double* val, int num);
double dF_33(double* val, int num);

int main() {
	/*
		初始化数表z-(t,u)
	*/
	numeric::NumberTableVar2<double> Ztu(6, 6);
	initFtu(&Ztu);
	//Ztu.print();

	/*
		初始化非线性方程组
	*/
	numeric::FUNC*	   F  = new  numeric::FUNC[4];
	numeric::FUNC**   dF  = new  numeric::FUNC*[4];
	for (int i = 0; i < 4; i++) {
		dF[i] = new numeric::FUNC[4];
	}
	//set F(x)
	F[0] = F_0;F[1] = F_1;F[2] = F_2;F[3] = F_3;
	//set dF(x)
	dF[0][0] = dF_00; dF[0][1] = dF_01; dF[0][2] = dF_02; dF[0][3] = dF_03;
	dF[1][0] = dF_10; dF[1][1] = dF_11; dF[1][2] = dF_12; dF[1][3] = dF_13;
	dF[2][0] = dF_20; dF[2][1] = dF_21; dF[2][2] = dF_22; dF[2][3] = dF_23;
	dF[3][0] = dF_30; dF[3][1] = dF_31; dF[3][2] = dF_32; dF[3][3] = dF_33;
	
	/*
		求解数表F-(x,y)
	*/
	numeric::NumberTableVar2<double> Fxy(11, 21);
	homework3::global_x = 0.0;
	homework3::global_y = 0.5;
	double sol[4] = { 0.01, 0.01, 0.01, 0.01 };//依次为:u,t,w,v
	for (int i = 0; i <= 10; i++) {
		homework3::global_x = 0.08*i;
		Fxy.var1[i] = homework3::global_x;
		for (int j = 0; j <= 20; j++) {
			homework3::global_y = 0.5 + 0.05*j;
			Fxy.var2[j] = homework3::global_y;
			//一组x,y 确定一个方程组，求解t,u
			numeric::NewtonMethodForNonLinearEquation(4, sol, F, dF);
			//在线插值求F(x,y)=Z(t,u)
			double fxy = numeric::DualQuadraticPiecewiseInterpolation(Ztu,sol[1],sol[0]);
			Fxy.value->set(i,j,fxy);
		}
	}
	printf("=================数表(x,y,f(x,y))===============\n");
	Fxy.print();
	printf("=================选择过程(k,sigma)===============\n");
	for (int k = 2; k < 10; k++) {
		numeric::Var2Polynomial<double> fitted =  numeric::LeastSquareSurfaceFitting<double>(Fxy, k);
		double sigma = 0.0;
		double tmp;
		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j <= 20; j++) {
				tmp = fitted.eval(Fxy.var1[i], Fxy.var2[j]) - Fxy.value->get(i, j);
				sigma += tmp*tmp;
			}
		}
		printf("k=%d,sigma=%+.12e\n",k, sigma);
		if (sigma <= 1e-7) {
			
			printf("=================拟合系数Crs===============\n");
			fitted.print();
			printf("=============数表(x,y,f(x,y),p(x,y))=======\n");
			for (int i = 1; i <= 8; i++) {
				homework3::global_x = 0.1*i;
				for (int j = 1; j <= 5; j++) {
					homework3::global_y = 0.5 + 0.2*j;
					//解出t,u
					numeric::NewtonMethodForNonLinearEquation(4, sol, F, dF);
					//在线插值求F(x,y)=Z(t,u)
					double fxy = numeric::DualQuadraticPiecewiseInterpolation(Ztu, sol[1], sol[0]);
					printf("[x_%d, y_%d, f(x_%d, y_%d), p(x_%d, y_%d)] = [%lf, %lf, %+.12e, %+.12e]\n",
						i, j, i, j, i, j, homework3::global_x, homework3::global_y,
						fxy, fitted.eval(homework3::global_x, homework3::global_y)
					);
				}
			}

			break;
		}
	}
	

	delete[] F;
	for (int i = 0; i < 4; i++) {
		delete[] dF[i];
	}
	delete[] dF;
	system("pause");
}

void initFtu(numeric::NumberTableVar2<double>* table) {
	table->var1[0] = 0; table->var1[1] = 0.2; table->var1[2] = 0.4;
	table->var1[3] = 0.6; table->var1[4] = 0.8; table->var1[5] = 1.0;//t

	table->var2[0] = 0; table->var2[1] = 0.4; table->var2[2] = 0.8;
	table->var2[3] = 1.2; table->var2[4] = 1.6; table->var2[5] = 2;//u

	double val[6][6] = {
		{ -0.5, -0.34, 0.14, 0.94, 2.06, 3.5 },
		{ -0.42, -0.5, -0.26, 0.3, 1.18, 2.38 },
		{ -0.18, -0.5, -0.5, -0.18, 0.46, 1.42 },
		{ 0.22, -0.34, -0.58, -0.5, -0.1, 0.62 },
		{ 0.78, -0.02, -0.5, -0.66, -0.5, -0.02 },
		{ 1.5, 0.46, -0.26, -0.66, -0.74, -0.5 },
	};

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			table->value->set(i, j, val[i][j]);
		}
	}
}
/*
	x,y is constant
	val = {u,t,w,v}
	F_0 = u + 0.5cost +  w + v - 2.67 - x
	F_1 = t + 0.5 sinu + w + v - 1.07 -y
	F_2 = w + 0.5t + u + cosv - 3.74 - x 
	F_3 = v + t + 0.5u + sinw - 0.79 - y
*/
double F_0(double* val, int num) {
	return (val[0] + 0.5*cos(val[1]) + val[2] + val[3] - 2.67 - homework3::global_x);
}
double F_1(double* val, int num) {
	return (val[1] + 0.5*sin(val[0]) + val[2] + val[3] - 1.07 - homework3::global_y);
}
double F_2(double* val, int num) {
	return (val[2] + 0.5*val[1] + val[0] + cos(val[3]) - 3.74 - homework3::global_x);
}
double F_3(double* val, int num) {
	return (val[3] + val[1] + 0.5*val[0] + sin(val[2]) - 0.79 -homework3::global_y);
}

double dF_00(double* val, int num) {  return 1.0; }
double dF_01(double* val, int num) {  return -0.5*sin(val[1]); }
double dF_02(double* val, int num) {  return 1.0; }
double dF_03(double* val, int num) {  return 1.0; }

double dF_10(double* val, int num) {  return 0.5*cos(val[0]); }
double dF_11(double* val, int num) {  return 1.0; }
double dF_12(double* val, int num) {  return 1.0; }
double dF_13(double* val, int num) {  return 1.0; }

double dF_20(double* val, int num) {  return 1.0; }
double dF_21(double* val, int num) {  return 0.5; }
double dF_22(double* val, int num) {  return 1.0; }
double dF_23(double* val, int num) {  return -sin(val[3]); }

double dF_30(double* val, int num) {  return 0.5; }
double dF_31(double* val, int num) {  return 1.0; }
double dF_32(double* val, int num) {  return cos(val[2]); }
double dF_33(double* val, int num) {  return 1.0; }