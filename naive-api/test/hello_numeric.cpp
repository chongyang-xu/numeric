#include<iostream>
#include<memory>
#include "numeric.h"

using namespace numeric;
using namespace std;

int main(){
	shared_ptr<Mat<float>> pmat(new Mat<float>(5,4));
	shared_ptr<Vec<float>> pvec(new Vec<float>(5));
	
	pmat->Copy();
	int m = pmat->get_m();
	int n = pmat->get_n();
	
	pvec->Copy();
	pvec->Scale(1.0);
	pvec->get_m();
	pvec->Dot(pvec);
	
	
	shared_ptr<Mat<float>> pmat2 = pmat->Add(pmat, nullptr);
	shared_ptr<Mat<float>> pmat3 = pmat->MulMat(pmat, nullptr, false);
	//shared_ptr<Mat<float>> invp = Inverse(pmat);
	PowerMinEigen<float>(pmat, pvec);	
	pmat->MulVec(pvec, nullptr, false);

}
