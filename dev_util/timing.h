#ifndef DEV_UTIL_TIMING_H
#define DEV_UTIL_TIMINH_H

#include <chrono>
#include <iostream>

#define TIK(name) auto __FILE__##name##_begin = std::chrono::high_resolution_clock::now()

#define TOK(name) auto __FILE__##name##_end = std::chrono::high_resolution_clock::now(); \
		  double __FILE__##name##_ms = std::chrono::duration_cast<std::chrono::milliseconds>(__FILE__##name##_end - __FILE__##name##_begin).count(); \
		  std::cout << "[Timer][" <<__FILE__<<"]["<<#name<<"][" <<__FILE__##name##_ms <<"][ms]"<<std::endl
		


#define TIMER(name) \
std::chrono::time_point<std::chrono::high_resolution_clock> __FILE__##name##_tik, __FILE__##name##_tok; \
auto __FILE__##name##_sum = (__FILE__##name##_tik - __FILE__##name##_tik)

#define PICK_TIK(name) do{__FILE__##name##_tik = std::chrono::high_resolution_clock::now();}while(0)

#define PICK_TOK(name) do{__FILE__##name##_tok = std::chrono::high_resolution_clock::now(); \
			  __FILE__##name##_sum += (__FILE__##name##_tok - __FILE__##name##_tik);}while(0)

#define TIMESUM(name) do{ \
double __FILE__##name##_ms = std::chrono::duration_cast<std::chrono::milliseconds>(__FILE__##name##_sum).count();\
std::cout << "[Timer][" <<__FILE__<<"]["<<#name<<"][" <<__FILE__##name##_ms <<"][ms]"<<std::endl;}while(0)

#endif
