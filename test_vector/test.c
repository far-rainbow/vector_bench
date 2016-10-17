/*
 * test.c
 *
 *  Created on: 08 04 2015
 *      Author: administrator
 *
 *  Notebook edition
 */

// BUILD IT WITH -O0 and -msse options to see most difference
//
// benchmark array size (floats) here!
#define FLOAT_ARRAY_SIZE 32000000

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "test.h"

int main()
{
	struct timeval timeStart, timeEnd;
	struct timeval timeFloatAddStart, timeVectorAddStart;
	struct timeval timeFloatAddEnd, timeVectorAddEnd;
	double elapsedTime;

	gettimeofday(&timeStart, NULL);

	//	two input arrays and one output (A + B = C)
	//	that`s test =)
	float *fA = (float *) malloc(sizeof(float) * FLOAT_ARRAY_SIZE);
	float *fB = (float *) malloc(sizeof(float) * FLOAT_ARRAY_SIZE);
	float *fC = (float *) malloc(sizeof(float) * FLOAT_ARRAY_SIZE);

	// init input arrays with some rubbish
	// INIT_GROW is +1 sequence of values start with valueA for vA (this start = 111) and valueB for vB (this start = 222)
	// so first value in vC shall be 333.
	// INIT_EASY is just a fill with valueA
	initFloatAB(fA, fB, INIT_GROW, 111, 222);

	// A + B = C with default float arrays
	gettimeofday(&timeFloatAddStart, NULL);
	floatArrayAdd(fA, fB, fC);
	gettimeofday(&timeFloatAddEnd, NULL);

	// two input arrays and one output (A + B = C)
	// with using type of vecm, so tests must be done with
	// variation of compilers and optimization flags to catch and see the difference
	vecm *vA = (vecm *) malloc(sizeof(vecm) * VECTOR_ARRAY_SIZE);
	vecm *vB = (vecm *) malloc(sizeof(vecm) * VECTOR_ARRAY_SIZE);
	vecm *vC = (vecm *) malloc(sizeof(vecm) * VECTOR_ARRAY_SIZE);

	// init input arrays with some rubbish
	// INIT_GROW is +1 sequence of values start with valueA for vA (this start = 111) and valueB for vB (this start = 222)
	// so first value in vC shall be 333.
	// INIT_EASY is just a fill with valueA
	initVectorFloatAB(vA, vB, INIT_GROW, 111, 222);

	// A + B = C with vector array and vector type operation
	gettimeofday(&timeVectorAddStart, NULL);
	floatVectorArrayAdd(vA, vB, vC);
	gettimeofday(&timeVectorAddEnd, NULL);

	//fprintresult(fA, fB, fC);
	//vprintresult(vA, vB, vC);

	printf("Bench addition of two %d-element arrays of float:\n", FLOAT_ARRAY_SIZE);

	//printFloatArrays(fA,fB,fC);
	//printVectorArrays(vA,vB,vC);

	// free memory (compatibilty with some old compilers)
	free(fA);
	free(fB);
	free(fC);
	free(vA);
	free(vB);
	free(vC);

	gettimeofday(&timeEnd, NULL);

	elapsedTime = (timeEnd.tv_sec - timeStart.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (timeEnd.tv_usec - timeStart.tv_usec) / 1000.0;   // us to ms

	printf("\nTotal time with memory allocation/free is: %.2f ms\n",elapsedTime);

	elapsedTime = (timeFloatAddEnd.tv_sec - timeFloatAddStart.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (timeFloatAddEnd.tv_usec - timeFloatAddStart.tv_usec) / 1000.0;   // us to ms

	printf("\nAddition of two arrays of float[%d]: %.2f ms\n",FLOAT_ARRAY_SIZE,elapsedTime);

	elapsedTime = (timeVectorAddEnd.tv_sec - timeVectorAddStart.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (timeVectorAddEnd.tv_usec - timeVectorAddStart.tv_usec) / 1000.0;   // us to ms

	printf("\nAddition of two arrays of vector float[%d]: %.2f ms\n",FLOAT_ARRAY_SIZE,elapsedTime);

	return (0);
}

void initFloatAB(float *fA, float *fB, int mode, int valueA, int valueB)
{
	switch (mode)
	{
	case INIT_EASY:
		initFloatArray(fA, INT, valueA, ZERO);
		initFloatArray(fB, INT, valueB, ZERO);
		break;
	case INIT_GROW:
		initFloatArray(fA, GROW, valueA, ZERO);
		initFloatArray(fB, GROW, valueB, ZERO);
		break;
	default:
		break;
	}
}

void initVectorFloatAB(vecm *vA, vecm *vB, int mode, int valueA, int valueB)
{
	switch (mode)
	{
	case INIT_EASY:
		initVectorArray(vA, INT, valueA, ZERO);
		initVectorArray(vB, INT, valueB, ZERO);
		break;
	case INIT_GROW:
		initVectorArray(vA, GROW, valueA, valueB);
		initVectorArray(vB, GROW, valueB, valueA);
		break;
	default:
		break;
	}
}

// valueB is not used. future feature stub
void initFloatArray(float *fA, int initMode, int valueA, int valueB)
{
	int i;
	switch (initMode)
	{
	case INT:
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++)
		{
			fA[i] = (float) valueA;
		}
		break;
	case GROW:
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++)
		{
			fA[i] = (float)valueA++ / 3.14159;
		}
		break;
	default:
		break;
	}
}

// valueB is not used. future feature stub
void initVectorArray(vecm *vA, int initMode, int valueA, int valueB)
{
	int i, j;
	float *vfA;
	switch (initMode)
	{
	case INT:
		for (i = 0; i < VECTOR_ARRAY_SIZE; i++)
		{
			vfA = (float *) &vA[i];
			for (j = 0; j < VECTORSIZE; j++)
			{
				vfA[j] = valueA;
			}
		}
		break;
	case GROW:
		for (i = 0; i < VECTOR_ARRAY_SIZE; i++)
		{
			vfA = (float *) &vA[i];
			for (j = 0; j < VECTORSIZE; j++)
			{
				vfA[j] = valueA++ / 3.14159;
			}
		}
		break;
	default:
		break;
	}
}

void floatArrayAdd(float *fA, float *fB, float *fC)
{
	int i;
	for (i = 0; i < FLOAT_ARRAY_SIZE; i++)
	{
		fC[i] = fA[i] + fB[i];
	}
}

void floatVectorArrayAdd(vecm *vA, vecm *vB, vecm *vC)
{
	int i;
	for (i = 0; i < VECTOR_ARRAY_SIZE; i++)
	{
		vC[i] = vA[i] + vB[i];
	}
}

void printFloatArrays(float *fA, float *fB, float *fC)
{
	int i;
	for (i = 0; i < FLOAT_ARRAY_SIZE; i++)
	{
		printf("farray #%d: (A)%f + (B)%f = (C)%f\n", i, fA[i], fB[i], fC[i]);
	}
}

void printVectorArrays(vecm *vA, vecm *vB, vecm *vC)
{
	int i, j;
	float *vfA;
	float *vfB;
	float *vfC;
	for (i = 0; i < VECTOR_ARRAY_SIZE; i++)
	{
		vfA = (float *) &vA[i];
		vfB = (float *) &vB[i];
		vfC = (float *) &vC[i];
		for (j = 0; j < VECTORSIZE; j++)
		{
			printf("vector array element [#%d]: (A) %f + (B) %f = (C) %f\n", i * VECTORSIZE + j,
					vfA[j], vfB[j], vfC[j]);
		}
	}
}


