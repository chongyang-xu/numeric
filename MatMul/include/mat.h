#ifndef   PARALLEL_MAT_H
#define   PARALLEL_MAT_H

#include<iostream>
#include<cstdlib>
#include<mkl.h>

enum kMatInitType {ZERO, ONE, RAND, NOT} ; 

struct Mat{
Mat(int m_, int n_, kMatInitType type){
    row =  m_;
    col =  n_;
#ifdef MKL
    data = static_cast<float*>( mkl_malloc(m_*n_*sizeof(float), 256) );
#else
    data = static_cast<float*>( malloc(m_*n_*sizeof(float)) );
#endif

switch(type){
    case ZERO:
        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++)        
                data[col*i+j] = 0;
        break;
    case ONE:
        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++)        
                data[col*i+j] = 1.0;
        break;
    case RAND:
        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++)        
                data[col*i+j] = rand()%10 /10.0;
        break;
    default:
        break;
    }
//    LOG_INFO()<<"CreateMat()"<<LOG_END;    
}
~Mat(){
#ifdef MKL
      mkl_free(data);
#else
      free(data);
#endif
//    LOG_INFO()<<"ReleaseMat()"<<LOG_END;    
}
void Print(){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){      
               std::cout<< data[col*i+j]<<" ";
            }
            std::cout <<std::endl;
        }
}
float* data;
int row,col;
};

#endif
