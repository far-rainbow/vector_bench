/*
 * test.h
 *
 *  Created on: 09 04 2015
 *      Author: administrator
 */

#ifndef TEST_H_
#define TEST_H_

#define fSIZE 1024*1024
#define vSIZE fSIZE/VECTORSIZE

#define NAR 0

#define INIT_EASY 1
#define INIT_GROW 2

#define INT 1
#define GROW 2

#define VECTORSIZE 4
typedef float __attribute__((vector_size (sizeof(float) * VECTORSIZE))) vecm;

void finit(float *, int, int, int);
void vinit(vecm *, int, int, int);
void finit2(float *, float *, int, int, int);
void vinit2(vecm *, vecm *, int, int, int);
void fadd(float *, float *, float *);
void vadd(vecm *, vecm *, vecm *);
void fprintresult(float *, float *, float *);
void vprintresult(vecm *, vecm *, vecm *);
void printvector(vecm *, char *);

#endif /* TEST_H_ */
