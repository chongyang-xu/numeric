#include "prof.h"
#include "timing.h"

#define L 500
int a[L][L];
int b[L][L];
int c[L][L];

int aa[L][L];
int bb[L][L];
int cc[L][L];

void f1(){
	for(int i=0;i<L;i++){
		for(int j=0;j<L;j++){
			for(int k=0;k<L;k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}
void f2(){
	for(int i=0;i<L;i++){
		for(int k=0;k<L;k++){
			for(int j=0;j<L;j++){
				cc[i][j] += aa[i][k] * bb[k][j];
			}
		}
	}
}
int main(){

	Prof::profile("ijk",[&](){
		f1();
	});
	
	Prof::profile("ikj",[&](){
		f2();
	});
}
