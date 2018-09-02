#include<algorithm>

#include<mkl.h>
#include<immintrin.h>
#include<omp.h>

#include "matmul.h"


// one cpu thread mat mul
// C mn = A mk  *  B kn
//  L1d cache 32k
//  L2 cache 256k
//  L3 cache 35M

void STMatMulNaive(float* A, float* B, float*C, int Cm, int Ak, int Cn){
    for(int i=0; i<Cm; i++){
        for( int k=0; k<Ak; k++){
            for( int j=0; j<Cn; j++){
                C[i*Cn+ j] += A[i*Ak + k] * B[k*Cn+j];
            }
        }
    }
}


void STMatMulStupid(float* A, float* B, float*C, int Cm, int Ak, int Cn){
    
    const static int L1_BLOCKSIZE_I   = 96;  
    const static int L1_BLOCKSIZE_J   = 96; 
    const static int L1_BLOCKSIZE_K   = 96;  

    const static int SIMD_WIDTH_J   = 8;

    for(int i1  = 0; i1 < Cm;  i1 += L1_BLOCKSIZE_I){
    for(int j1  = 0; j1 < Cn;  j1 += L1_BLOCKSIZE_J){
    for(int k1  = 0; k1 < Ak;  k1 += L1_BLOCKSIZE_K){
            int end_n = std::min(Cn, j1+SIMD_WIDTH_J);
            __m256 c_acc;
            __m256 a;
            __m256 b;
            for(int is = i1; is < Cm; is ++){
                for(int js = j1; js < end_n; js += SIMD_WIDTH_J){
                    c_acc = _mm256_load_ps( &C[is*Cn + js] );
                    for(int ks = k1; ks < Ak; ks ++){
                        a = _mm256_set1_ps( A [is*Ak + ks]);
                        b = _mm256_load_ps( &B[ks*Cn + js] );
                        _mm256_fmadd_ps(a, b, c_acc);
                    }
                    _mm256_store_ps( &C[is*Cn + js] , c_acc);
                }
            }
    }
    }
    }
}


//learned from https://github.com/HazyResearch/blocking-tutorial
// http://www.cs.utexas.edu/users/flame/pubs/blis3_ipdps14.pdf
namespace {
typedef float aligned_float __attribute__((__aligned__(256)));

/*
 * A mxk ,B kxn, C mxn
 *
 *  block : 16 col, 6 rows
 *
 *  |XXXXXXXX|XXXXXXXX|     |OOOOOOOOOOOOOOO|* |UUUUUUUU|UUUUUUUU|
 *  |XXXXXXXX|XXXXXXXX|     |OOOOOOOOOOOOOOO|  

 *  |XXXXXXXX|XXXXXXXX| +=  |OOOOOOOOOOOOOOO| 
 *  |XXXXXXXX|XXXXXXXX|     |OOOOOOOOOOOOOOO|  

 *  |XXXXXXXX|XXXXXXXX|     |OOOOOOOOOOOOOOO|  |UUUUUUUU|UUUUUUUU|
 *  |XXXXXXXX|XXXXXXXX|     |OOOOOOOOOOOOOOO|  |UUUUUUUU|UUUUUUUU|
 *  6x2=12 regs             2 reg for a        |UUUUUUUU|UUUUUUUU|
 *                          2 reg for b        |UUUUUUUU|UUUUUUUU|
 *  12+2+2 = 16 regs                           |UUUUUUUU|UUUUUUUU|
 *  "tiling" for "regs"                        |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *                                             |UUUUUUUU|UUUUUUUU|
 *
 * */

inline void matmul_kernel_blocked_16_6(
    const aligned_float* __restrict__   A,
    const aligned_float* __restrict__   B,
          aligned_float*                C,
    const int M, const int N, const int K,
    const int jc, const int nc,
    const int pc, const int kc,
    const int ic, const int mc,
    const int jr, const int nr,
    const int ir, const int mr
)
{
    // total 16 vec regs
    // 12 register for C
    // 2  register for A
    // 2  register for B
    // reason for this is:
    //
    
    // acc sum, init to 0 vec
    // acc for one |XXXXXXXX|
    __m256 result_0_0 = _mm256_set1_ps(0);
    __m256 result_1_0 = _mm256_set1_ps(0);
    __m256 result_2_0 = _mm256_set1_ps(0);
    __m256 result_3_0 = _mm256_set1_ps(0);
    __m256 result_4_0 = _mm256_set1_ps(0);
    __m256 result_5_0 = _mm256_set1_ps(0);
    __m256 result_0_1 = _mm256_set1_ps(0);
    __m256 result_1_1 = _mm256_set1_ps(0);
    __m256 result_2_1 = _mm256_set1_ps(0);
    __m256 result_3_1 = _mm256_set1_ps(0);
    __m256 result_4_1 = _mm256_set1_ps(0);
    __m256 result_5_1 = _mm256_set1_ps(0);

    //two value from same col
    __m256 A0;
    __m256 A1;
    //tow vec from same row
    __m256 B0;
    __m256 B1;

    
    //iter on k, acc for c
    for(int k=0; k < kc; k++){
        
         __builtin_prefetch(&B[N*(k+1+pc)+jc+jr+8*0]);
         __builtin_prefetch(&B[N*(k+1+pc)+jc+jr+8*1]);

        B0 = _mm256_load_ps( &B[ (pc+k)*N + jc + jr + 0*8 ] );
        B1 = _mm256_load_ps( &B[ (pc+k)*N + jc + jr + 1*8 ] );

        A0 = _mm256_set1_ps(  A[ (ic+ir+0)*K + pc + k] );
        A1 = _mm256_set1_ps(  A[ (ic+ir+1)*K + pc + k] );

        result_0_0 = _mm256_fmadd_ps(A0, B0, result_0_0);
        result_0_1 = _mm256_fmadd_ps(A0, B1, result_0_1);
        result_1_0 = _mm256_fmadd_ps(A1, B0, result_1_0);
        result_1_1 = _mm256_fmadd_ps(A1, B1, result_1_1);

        
        A0 = _mm256_set1_ps(  A[ (ic+ir+2)*K + pc + k] );
        A1 = _mm256_set1_ps(  A[ (ic+ir+3)*K + pc + k] );
        result_2_0 = _mm256_fmadd_ps(A0, B0, result_2_0);
        result_2_1 = _mm256_fmadd_ps(A0, B1, result_2_1);
        result_3_0 = _mm256_fmadd_ps(A1, B0, result_3_0);
        result_3_1 = _mm256_fmadd_ps(A1, B1, result_3_1);


        A0 = _mm256_set1_ps(  A[ (ic+ir+4)*K + pc + k] );
        A1 = _mm256_set1_ps(  A[ (ic+ir+5)*K + pc + k] );
        result_4_0 = _mm256_fmadd_ps(A0, B0, result_4_0);
        result_4_1 = _mm256_fmadd_ps(A0, B1, result_4_1);
        result_5_0 = _mm256_fmadd_ps(A1, B0, result_5_0);
        result_5_1 = _mm256_fmadd_ps(A1, B1, result_5_1);

    }

      //write reg back to c
     *( (__m256*) (&C[ (ic+ir+0)*N + jc+jr+0*8]) ) += result_0_0;
     *( (__m256*) (&C[ (ic+ir+1)*N + jc+jr+0*8]) ) += result_1_0;
     *( (__m256*) (&C[ (ic+ir+2)*N + jc+jr+0*8]) ) += result_2_0;
     *( (__m256*) (&C[ (ic+ir+3)*N + jc+jr+0*8]) ) += result_3_0;
     *( (__m256*) (&C[ (ic+ir+4)*N + jc+jr+0*8]) ) += result_4_0;
     *( (__m256*) (&C[ (ic+ir+5)*N + jc+jr+0*8]) ) += result_5_0;

     *( (__m256*) (&C[ (ic+ir+0)*N + jc+jr+1*8]) ) += result_0_1;
     *( (__m256*) (&C[ (ic+ir+1)*N + jc+jr+1*8]) ) += result_1_1;
     *( (__m256*) (&C[ (ic+ir+2)*N + jc+jr+1*8]) ) += result_2_1;
     *( (__m256*) (&C[ (ic+ir+3)*N + jc+jr+1*8]) ) += result_3_1;
     *( (__m256*) (&C[ (ic+ir+4)*N + jc+jr+1*8]) ) += result_4_1;
     *( (__m256*) (&C[ (ic+ir+5)*N + jc+jr+1*8]) ) += result_5_1;

}//end matmul_kkernel

}//end namespace

void STMatMul(float* A, float* B, float*C, int M, register int N, register int K){
    
    // L1 cache 32k
    // L2 cache 256k
    // L3 cache 35M
    // simd regs 16
    
    // nr is 16, mr is 6
    // kc*16 fits 32K  L1 => kc
    // kc*mc fits 256k L2 => mc
    // kc* nc fits 35M L3 => nc

    const int nc = N;
    const int kc = 240;
    const int mc = 120;
    
    const int nr = 16;
    const int mr = 6;

    for(int jc = 0; jc < N; jc += nc){
        for(int pc = 0; pc < K; pc += kc){
            for(int ic = 0; ic < M; ic += mc){
                for(int jr = 0; jr < nc; jr += nr){
                    for(int ir = 0; ir < mc; ir += mr){
                        matmul_kernel_blocked_16_6(A, B, C, M, N, K, jc, nc, pc, kc, ic, mc, jr, nr, ir, mr );                    
                    }
                }
            }
        }
    }
}

void MTMatMul(float* A, float* B, float*C, int M, int N, int K){
    
    // L1 cache 32k
    // L2 cache 256k
    // L3 cache 35M
    // simd regs 16
    
    // nr is 16, mr is 6
    // kc*16 fits 32K  L1 => kc
    // kc*mc fits 256k L2 => mc
    // kc* nc fits 35M L3 => nc

    const int nc = N;
    const int kc = 240;
    const int mc = 120;
    
    const int nr = 16;
    const int mr = 6;
    
    omp_set_num_threads(24);

    for(int jc = 0; jc < N; jc += nc){
        for(int pc = 0; pc < K; pc += kc){
            for(int ic = 0; ic < M; ic += mc){
                #pragma omp parallel for
                for(int jr = 0; jr < nc; jr += nr){
                    for(int ir = 0; ir < mc; ir += mr){
                        matmul_kernel_blocked_16_6(A, B, C, M, N, K, jc, nc, pc, kc, ic, mc, jr, nr, ir, mr );                    
                    }
                }
            }
        }
    }
}

void MatMulMKL(float* A, float* B, float*C, int M, int N, int K){
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 1.0, A, M, B, K, .0, C, M);
}
