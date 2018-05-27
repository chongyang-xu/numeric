#include "unit_test.h"

TEST_CASE(HELLO_WORLD)
{

	int a=10;int b=1;
	int expect=1024;

	EXPECT_EQ(b<<a, expect);
	EXPECT_NE(a<<b, expect);
	
}
int main(){}
