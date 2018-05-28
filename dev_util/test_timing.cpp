#include "timing.h"

#define L 500
int a[L][L];
int b[L][L];
int c[L][L];

int aa[L][L];
int bb[L][L];
int cc[L][L];
int main(){

	TIK(FOR_i_j_k);
	TIMER(ijk_acc);
	for(int i=0;i<L;i++){
		if(i%2==0)PICK_TIK(ijk_acc);
		for(int j=0;j<L;j++){
			for(int k=0;k<L;k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
		if(i%2==0)PICK_TOK(ijk_acc);
	}
	TIMESUM(ijk_acc);
	TOK(FOR_i_j_k);

	TIK(FOR_i_k_j);
	for(int i=0;i<L;i++){
		for(int k=0;k<L;k++){
			for(int j=0;j<L;j++){
				cc[i][j] += aa[i][k] * bb[k][j];
			}
		}
	}
	TOK(FOR_i_k_j);

	return 0;
}
