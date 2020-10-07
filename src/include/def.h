#ifndef TEST_H_
#define TEST_H_

#include <omp.h>

/* benchmark array size (floats) here! */
#define FLOAT_ARRAY_SIZE 50000000
#define DEBUG_LINES 4
#define BENCH_PASSES 32
/*-------------------------------------*/

#define ZERO 0

#define INIT_EASY 1
#define INIT_GROW 2

#define INT 1
#define GROW 2

#define TEST_0 0
#define TEST_1 1

#define VECTORSIZE 4 /* does it going right? */

typedef float __attribute__ ((vector_size (sizeof(float) * VECTORSIZE))) vecm;

#define VECTOR_ARRAY_SIZE FLOAT_ARRAY_SIZE/VECTORSIZE

void initFloatArraySIMD(float *, int, int, int);
void initFloatArraySIMDMP(float *, int, int, int);

void initFloatArray(float *, int, int, int);
void initVectorArray(vecm *, int, int, int);

void initFloatAB(float *, float *, int, int, int);
void initVectorFloatAB(vecm *, vecm *, int, int, int);

void floatArrayAdd(float *, float *, float *);
void floatVectorArrayAdd(vecm *, vecm *, vecm *);

void printFloatArrays(float *, float *, float *, int);
void printVectorArrays(vecm *, vecm *, vecm *,int);

#include <sys/time.h>

typedef void (*pF)(float *,float *,int,int,int);
void benchIT(struct timeval*,struct timeval*, pF );

int testing (int , int );

#endif /* TEST_H_ */
