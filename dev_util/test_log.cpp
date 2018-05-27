#include"log.h"
#include<string>

int main(){
	char cc[20]={};
	LOG_INFO(0)<<"test with tag" << cc << LOG_END;
	LOG_INFO()<<"test with tag"  << LOG_END;
	int a=0, b=1;
	LOG_INFO_IF(a<b, 0) <<"test with if " << (a<b) <<LOG_END;
	LOG_INFO_IF(a>b, 0) <<"test with if " << (a>b) <<LOG_END;
	
	LOG_ERR(0)<<"test with tag" << 0 << LOG_END;
	LOG_ERR()<<"test with tag"  << LOG_END;

	LOG_ERR_IF(a<b, 0) <<"test with if" <<(a<b) <<LOG_END;
	LOG_ERR_IF(a>b, 0) <<"test with if" <<(a>b) <<LOG_END;
	
	std::string str1="aaa", str2="aaa", str3="abc";
	CHECK(false) <<"hehe"<<CHECK_END;
	//CHECK_EQ(str1, str3)<<"string should equal" <<CHECK_END;
	CHECK_EQ(2.0000, 2) <<"hehe"<<CHECK_END;
	//CHECK_NE(str1, str2)<<"string should not equal" <<CHECK_END;
	//CHECK_GT(str1, str2)<<"string should str1>str2" <<CHECK_END;
	//CHECK_GE(str1, str3)<<"string should str1>= str2 equal" <<CHECK_END;
	//CHECK_NE(str1, str2)<<"string should not equal" <<CHECK_END;
	//CHECK_LT(str1, str2)<<"string should str1<str2equal" <<CHECK_END;
	CHECK_LE(str1, str3)<<"string should equal" <<CHECK_END;
	
	int *p1=0;
	int *p2=NULL;
	int *p3=nullptr;
	//CHECK_NOT_NULL(p1)<<"should not null"<<CHECK_END;
	//CHECK_NOT_NULL(p2)<<"should not null"<<CHECK_END;
	//CHECK_NOT_NULL(p3)<<"should not null"<<CHECK_END;
}
