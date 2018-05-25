#ifndef NUMERIC_MAT_VEC_H
#define NUMERIC_MAT_VEC_H
namespace numeric{
using shared_ptr = std::shared_ptr
template<typename T>
class Mat{
public:
	Mat(int m, int n);
	~Mat();
	
	get_m();
	get_n();

	inline operator [][](int i, int j);
	
	shared_ptr<Mat> Copy();
	shared_ptr<Mat> Select(int m, int n, int beg=0, int end=0);

	shared_ptr<Mat> Add(shared_ptr<Mat> b, shared_ptr<T> alpha=shared_ptr<T>());
	shared_ptr<Mat> Sub(shared_ptr<Mat> b, shared_ptr<T> alpha=shared_ptr<T>());
	shared_ptr<Mat> Mul(shared_ptr<Mat> b, shared_ptr<T> alpha=shared_ptr<T>(), bool trans=false);
	//shared_ptr<Mat> MulAdd(shared_ptr<Mat> b, shared_ptr<T> p=shared_ptr<T>(), bool trans=false);
	shared_ptr<Vec> Mul(shared_ptr<Vec> b, shared_ptr<T> alpha=shared_ptr<T>(), bool trans=false);
	//shared_ptr<Vec> MulAdd(shared_ptr<Vec> b, shared_ptr<T> p=shared_ptr<T>(), bool trans=false);
	

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

	get_m();

	inline operator [](int i);

	shared_ptr<Vec> Copy();
	void 	Scale(T alpha);
	T	Norm2();
	
	T	Dot(shared_ptr<Vec> b);
	shared_ptr<Mat> Out(shared_ptr<Vec> b);
	shared_ptr<Vec>	Add(shared_ptr<Vec> b, shared_ptr<T> alpha=shared_ptr<T>());
 	shared_ptr<Vec> Sub(shared_ptr<Vec> b, shared_ptr<T> alpha=shared_ptr<T>());	
 		
private:
	int m_;
	T* data_;
};


}

#endif
