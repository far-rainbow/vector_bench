/*
 * test.c
 *
 *  Created on: 08 04 2015
 *      Author: administrator
 *
 *  Notebook edition
 */

#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main()
{
	float *fA = (float *) malloc(sizeof(float) * fSIZE);
	float *fB = (float *) malloc(sizeof(float) * fSIZE);
	float *fC = (float *) malloc(sizeof(float) * fSIZE);

	vecm *vA = (vecm *) malloc(sizeof(vecm) * vSIZE);
	vecm *vB = (vecm *) malloc(sizeof(vecm) * vSIZE);
	vecm *vC = (vecm *) malloc(sizeof(vecm) * vSIZE);

	finit2(fA, fB, INIT_GROW, 111, 222);
	fadd(fA, fB, fC);
	free(fA);
	free(fB);
	free(fC);

	vinit2(vA, vB, INIT_GROW, 111, 222);
	vinit(vC, INT, 111, 0);
	vadd(vA, vB, vC);
	printvector(&vC[vSIZE - 1], "Last vector sum:");
	free(vA);
	free(vB);
	free(vC);

	//fprintresult(fA, fB, fC);
	//vprintresult(vA, vB, vC);

	printf("Test two %d bytes vector arrays add...\n", fSIZE);

	return (0);
}

void finit(float *fA, int mode, int xValue, int yValue)
{
	int i;
	switch (mode)
	{
	case INT:
		for (i = 0; i < fSIZE; i++)
		{
			fA[i] = (float) xValue;
		}
		break;
	case GROW:
		for (i = 0; i < fSIZE; i++)
		{
			fA[i] = (float) xValue++;
		}
		break;
	default:
		break;
	}
}

void vinit(vecm *vA, int mode, int xValue, int yValue)
{
	int i, j;
	float *vfA;
	switch (mode)
	{
	case INT:
		for (i = 0; i < vSIZE; i++)
		{
			vfA = (float *) &vA[i];
			for (j = 0; j < VECTORSIZE; j++)
			{
				vfA[j] = xValue;
				//printf("vfA %f\n",vfA[j]);
			}
		}
		break;
	case GROW:
		for (i = 0; i < vSIZE; i++)
		{
			vfA = (float *) &vA[i];
			for (j = 0; j < VECTORSIZE; j++)
			{
				vfA[j] = xValue++;
				//printf("vfA %f\n",vfA[j]);
			}
		}
		break;
	default:
		break;
	}
}

void finit2(float *fA, float *fB, int mode, int xValue, int yValue)
{
	switch (mode)
	{
	case INIT_EASY:
		finit(fA, INT, xValue, NAR);
		finit(fB, INT, yValue, NAR);
		break;
	case INIT_GROW:
		finit(fA, GROW, xValue, NAR);
		finit(fB, GROW, yValue, NAR);
		break;
	default:
		break;
	}
}

void vinit2(vecm *vA, vecm *vB, int mode, int xValue, int yValue)
{
	switch (mode)
	{
	case INIT_EASY:
		vinit(vA, INT, xValue, NAR);
		vinit(vB, INT, yValue, NAR);
		break;
	case INIT_GROW:
		vinit(vA, GROW, xValue, yValue);
		vinit(vB, GROW, yValue, xValue);
		break;
	default:
		break;
	}
}

void fadd(float *fA, float *fB, float *fC)
{
	int i = 0;
	for (i = 0; i < fSIZE; i++)
	{
		fC[i] = fA[i] + fB[i];
	}
}

void vadd(vecm *vA, vecm *vB, vecm *vC)
{
	int i;
	for (i = 0; i < vSIZE; i++)
	{
		vC[i] = vA[i] + vB[i];
		//printvector(&vC[i],"debug vC ");
		//printf("i = %d\n",i);
	}
}

void fprintresult(float *fA, float *fB, float *fC)
{
	int i;
	for (i = 0; i < fSIZE; i++)
	{
		printf("farray #%d: (A)%f + (B)%f = (C)%f\n", i, fA[i], fB[i], fC[i]);
	}
}

void vprintresult(vecm *vA, vecm *vB, vecm *vC)
{
	int i, j;
	float *vfA;
	float *vfB;
	float *vfC;
	for (i = 0; i < vSIZE; i++)
	{
		vfA = (float *) &vA[i];
		vfB = (float *) &vB[i];
		vfC = (float *) &vC[i];
		for (j = 0; j < VECTORSIZE; j++)
		{
			printf("varray #%d: (A)%f + (B)%f = (C)%f\n", i * VECTORSIZE + j,
					vfA[j], vfB[j], vfC[j]);
		}
	}
}

void printvector(vecm *vA, char *debug)
{
	int i;
	float *vfA = (float *) vA;
	for (i = 0; i < VECTORSIZE; i++)
	{
		printf("debug %d vector print: %s = %f\n", i, debug, vfA[i]);
	}
	printf("--------------------------------------------------------\n");
}
