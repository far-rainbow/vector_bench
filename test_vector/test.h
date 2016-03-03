/*
 * test.h
 *
 *  Created on: 09 04 2015
 *      Author: administrator
 */

#ifndef TEST_H_
#define TEST_H_

#define ZERO 0

#define INIT_EASY 1
#define INIT_GROW 2

#define INT 1
#define GROW 2

#define VECTORSIZE 4 /* does it going right? */
typedef float __attribute__ ((vector_size (sizeof(float) * VECTORSIZE))) vecm;

#define VECTOR_ARRAY_SIZE FLOAT_ARRAY_SIZE/VECTORSIZE

void initFloatArray(float *, int, int, int);
void initVectorArray(vecm *, int, int, int);
void initFloatAB(float *, float *, int, int, int);
void initVectorFloatAB(vecm *, vecm *, int, int, int);
void floatArrayAdd(float *, float *, float *);
void floatVectorArrayAdd(vecm *, vecm *, vecm *);
void printFloatArrays(float *, float *, float *);
void printVectorArrays(vecm *, vecm *, vecm *);

#endif /* TEST_H_ */
