#include<memory>
#include<cmath>

#include "unit_test.h"
#include "timing.h"
#include "log.h"

#include "mat.h"
#include "matmul.h"

template<typename Type>
using SPtr = std::shared_ptr<Type>;

bool isEqual(SPtr<Mat> a, SPtr<Mat> b, float eta=1e-4){

    CHECK_EQ( a->row, b->row) <<"mat size != at m" <<CHECK_END;
    CHECK_EQ( a->col, b->col) <<"mat size != at n" << CHECK_END;

    float* a_ = a->data;
    float* b_ = b->data;
    float sum = 0;
    for(int i=0; i<a->row*a->col; i++){
           sum += fabs(a_[i]-b_[i]);
    }
    LOG_INFO(ErrorNorm) << sum << LOG_END;
    
    return true;
}

int dim  = 16*6*20;

SPtr<Mat> A( new Mat(dim,dim,ONE) );
SPtr<Mat> B( new Mat(dim,dim,ONE) );
SPtr<Mat> C( new Mat(dim,dim,ZERO) );
SPtr<Mat> D( new Mat(dim,dim,ZERO) );

TEST_CASE(MatrixMultiply){
    
    LOG_INFO(MatrixSize) << dim << LOG_END;
/*
    //test optimized  STMatMul
    //SPtr<Mat> flushCache( new Mat(dim<<4,dim<<4,RAND) );
    TIK(STMatMul);
    STMatMul(A->data, B->data, C->data, dim, dim, dim);
    TOK(STMatMul);

    //test optimized  MTMatMul
    //flushCache.reset( new Mat(dim<<4,dim<<4,RAND) );
    TIK(MTMatMul);
    MTMatMul(A->data, B->data, D->data, dim, dim, dim);
    TOK(MTMatMul);

    CHECK( isEqual(C, D) ) << CHECK_END;


    //test optimized  MatMulMKL
    D.reset( new Mat(dim,dim,ZERO) );
    //flushCache.reset( new Mat(dim<<4,dim<<4,RAND) );    
    TIK(MKL);
    MatMulMKL(A->data, B->data, D->data, dim, dim, dim);
    TOK(MKL);
    
    CHECK( isEqual(C, D) ) << CHECK_END;
    

    //test naive impl
    C.reset( new Mat(dim,dim,ZERO) );
    D.reset( new Mat(dim,dim,ZERO) );
    
    //flushCache.reset( new Mat(dim<<4,dim<<4,RAND) );
    TIK(naive);
    STMatMulNaive(A->data, B->data, C->data, dim, dim, dim);
    TOK(naive);
  */  
    //test a stupid tiling
    //flushCache.reset( new Mat(dim<<4,dim<<4,RAND) );
    TIK(stupid);
    STMatMulStupid(A->data, B->data, D->data, dim, dim, dim);
    TOK(stupid);
    

};


int main(){}
