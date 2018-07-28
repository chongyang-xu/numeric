#ifndef NUMERIC_MAT_VEC_H
#define NUMERIC_MAT_VEC_H
#include<memory>

namespace numeric{

using namespace std;

template<typename T>
class Vec;

template<typename T>
class Mat{
public:
	Mat(int m, int n);
	explicit Mat(std::string filename);
	~Mat();
	
	int get_m();
	int get_n();

	void operator [](int i);
	
	shared_ptr<Mat> Copy();
	shared_ptr<Mat> Select(int m, int n, int beg=0, int end=0);
	
	shared_ptr<Mat> Add(shared_ptr<Mat> b, shared_ptr<T> alpha);
	shared_ptr<Mat> Sub(shared_ptr<Mat> b, shared_ptr<T> alpha);
	shared_ptr<Mat> MulMat(shared_ptr<Mat> b, shared_ptr<T> alpha, bool trans);
	//shared_ptr<Mat> MulAdd(shared_ptr<Mat> b, shared_ptr<T> p=shared_ptr<T>(), bool trans=false);
	shared_ptr<Vec<T>> MulVec(shared_ptr<Vec<T>> b, shared_ptr<T> alpha, bool trans);
	//shared_ptr<Vec> MulAdd(shared_ptr<Vec> b, shared_ptr<T> p=shared_ptr<T>(), bool trans=false);
	
	void SaveTo(std::string filename);

private:
	int m_;
	int n_;
	T* data_;
};

template<typename T>
shared_ptr<Mat<T>> Inverse(shared_ptr<Mat<T>> m);

template<typename T>
T Det(shared_ptr<Mat<T>> m);

template<typename T>
T Cond(shared_ptr<Mat<T>> m);

template<typename T>
T Rank(shared_ptr<Mat<T>> m);

template<typename T>
T Norm2(shared_ptr<Mat<T>> m);


template<typename T>
class Vec{
public:
	explicit Vec(int m);
	~Vec();

	int get_m();

	void operator [](int i);

	shared_ptr<Vec> Copy();
	void 	Scale(T alpha);
	T	Norm2();
	
	T	Dot(shared_ptr<Vec> b);
	shared_ptr<Mat<T>> Out(shared_ptr<Vec> b);
	shared_ptr<Vec>	Add(shared_ptr<Vec> b, shared_ptr<T> alpha);
 	shared_ptr<Vec> Sub(shared_ptr<Vec> b, shared_ptr<T> alpha);	
 		
private:
	int m_;
	T* data_;
};

}

#endif
