#ifndef DEV_UTIL_LOG_H
#define DEV_UTIL_LOG_H

#include<iostream>
#include<ctime>

#define GET_LOCAL_TIME 				\
std::time_t dev_util_cur_time = std::time(0);	\
char cur_time[64];				\
std::strftime(cur_time, sizeof(cur_time), "%Y-%m-%d-%H-%M-%S", std::localtime(&dev_util_cur_time))


#define LOG_END		std::endl;}while(0)

#define LOG_INFO(tag)	\
do{			\
GET_LOCAL_TIME;		\
std::cout <<"[LOG_INFO]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]["<< #tag <<"]"

#define LOG_ERR(tag)	\
do{			\
GET_LOCAL_TIME;		\
std::cerr <<"[LOG_ERR][" <<  cur_time <<"]:[" << __FILE__ <<","<<__LINE__<<"]["<< #tag <<"]"

#define LOG_INFO_IF(cond, tag) if(cond) LOG_INFO(tag)
#define LOG_ERR_IF(cond, tag)  if(cond) LOG_ERR(tag)



#define CHECK_END	std::endl;throw 0;}}while(0)

#define CHECK(cond)  	\
do{			\
GET_LOCAL_TIME;		\
if(!(cond)){ 		\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_EQ(a, b)  \
do{			\
GET_LOCAL_TIME;		\
auto var_a = (a);	\
auto var_b = (b);	\
if(!(var_a == var_b)){ 	\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_NE(a, b)	\
do{                     \
GET_LOCAL_TIME;		\
auto var_a = (a);       \
auto var_b = (b);       \
if(!(var_a != var_b)){  \
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_GT(a, b)	\
do{                     \
GET_LOCAL_TIME;		\
auto var_a = (a);       \
auto var_b = (b);       \
if(!(var_a > var_b)){  	\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_GE(a, b)	\
do{                     \
GET_LOCAL_TIME;		\
auto var_a = (a);       \
auto var_b = (b);       \
if((var_a < var_b)){  	\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_LT(a, b)	\
do{                     \
GET_LOCAL_TIME;		\
auto var_a = (a);       \
auto var_b = (b);       \
if(!(var_a < var_b)){  	\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_LE(a, b)	\
do{                     \
GET_LOCAL_TIME;		\
auto var_a = (a);       \
auto var_b = (b);       \
if((var_a > var_b)){  	\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#define CHECK_NOT_NULL(p)		\
do{                     		\
GET_LOCAL_TIME;				\
if(p==nullptr || p==NULL || p==0){  	\
std::cout <<"[CHECK_FAIL]["<< cur_time <<"]:[" << __FILE__<<","<<__LINE__ <<"]"

#endif
