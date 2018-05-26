#ifndef DEV_UTIL_TIMING_H
#define DEV_UTIL_TIMINH_H

#include <chrono>
#include <iostream>

#define TIK(name) auto __FILE__##name##_begin = std::chrono::high_resolution_clock::now();

#define TOK(name) auto __FILE__##name##_end = std::chrono::high_resolution_clock::now(); \
		  double __FILE__##name##_ms = std::chrono::duration_cast<std::chrono::milliseconds>(__FILE__##name##_end - __FILE__##name##_begin).count(); \
		  std::cout << "[Timer][" <<__FILE__<<"]["<<#name<<"][" <<__FILE__##name##_ms <<"][ms]"<<std::endl;
		
#endif
