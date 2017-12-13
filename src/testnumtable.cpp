#include"numbertable.h"
#include"matrix.h"

#include<iostream>
using namespace numeric;
using namespace std;
int testnumtable() {
	NumberTableVar2<double> table(2, 3);

	table.var1[0] = 1; table.var1[1] = 2;
	table.var2[0] = 1.1; table.var2[1] = 2.2; table.var2[2] = 3.3;
	table.value->set(0, 0, 1); table.value->set(0, 1, 2); table.value->set(0, 2, 3);
	table.value->set(1, 0, 5); table.value->set(1, 1, 6); table.value->set(1, 2, 7);
	table.var1[0] = 1;
	table.print();
	system("pause");
	return 0;
}