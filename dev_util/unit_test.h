#ifndef  DEV_UTIL_UNIT_TEST_H
#define  DEV_UTIL_UNIT_TEST_H

#include <iostream>
#include <string>

#define TEST_CASE(NAME)						\
	extern void TEST_CASE_FUNCTION_##NAME(void);		\
	class TEST_CASE_CLASS_##NAME				\
	{							\
	public:							\
		TEST_CASE_CLASS_##NAME()			\
		{						\
			std::cout << #NAME << std::endl;	\
			TEST_CASE_FUNCTION_##NAME();		\
		}						\
	} TEST_CASE_INSTANCE_##NAME;				\
	void TEST_CASE_FUNCTION_##NAME(void)


#define EXPECT_EQ(a, b) \
do{			\
auto var_a = (a);	\
auto var_b = (b);	\
if(!(var_a == var_b)){ std::cout <<"[TEST_FAIL][EXPEC_EQ]: left: "<< var_a <<", right: "<< var_b<<std::endl; throw 0;}\
}while(0)


#define EXPECT_NE(a, b)	\
do{                     \
auto var_a = (a);       \
auto var_b = (b);       \
if((var_a == var_b)){ std::cout <<"[TEST_FAIL][EXPEC_NE]: left: "<< var_a <<", right: "<< var_b<<std::endl; throw 0;}\
}while(0)

#define EXPECT_GT(a, b)	\
do{                     \
auto var_a = (a);       \
auto var_b = (b);       \
if(!(var_a > var_b)){ std::cout <<"[TEST_FAIL][EXPEC_GT]: left: "<< var_a <<", right: "<< var_b<<std::endl; throw 0;}\
}while(0)

#define EXPECT_GE(a, b)	\
do{                     \
auto var_a = (a);       \
auto var_b = (b);       \
if((var_a < var_b)){ std::cout <<"[TEST_FAIL][EXPEC_GE]: left: "<< var_a <<", right: "<< var_b<<std::endl; throw 0;}\
}while(0)

#define EXPECT_LT(a, b)	\
do{                     \
auto var_a = (a);       \
auto var_b = (b);       \
if(!(var_a < var_b)){ std::cout <<"[TEST_FAIL][EXPEC_LT]: left: "<< var_a <<", right: "<< var_b<<std::endl; throw 0;}\
}while(0)

#define EXPECT_LE(a, b)	\
do{                     \
auto var_a = (a);       \
auto var_b = (b);       \
if(!(var_a > var_b)){ std::cout <<"[TEST_FAIL][EXPEC_LE]: left: "<< var_a <<", right: "<< var_b<<std::endl; throw 0;}\
}while(0)

#endif
