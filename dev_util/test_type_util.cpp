#include"type_util.h"

class Hello{
public:
	Hello(){}
	int a;

DENY_COPY_ASSIGN(Hello);
};

int main(){
	Hello a;
	Hello b;
	b  =  a;
	Hello c(a);
}
