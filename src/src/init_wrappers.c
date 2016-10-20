/*
 * init_wrappers.c
 *
 *  Created on: 20 окт. 2016 г.
 *      Author: test
 */

#include <def.h>

void initFloatAB(float *fA, float *fB, int mode, int valueA, int valueB) {
	switch (mode) {
	case INIT_EASY:
		initFloatArray(fA, INT, valueA, ZERO);
		initFloatArray(fB, INT, valueB, ZERO);
		break;
	case INIT_GROW:
		initFloatArraySIMDMP(fA, GROW, valueA, ZERO);
		initFloatArraySIMDMP(fB, GROW, valueB, ZERO);

		//initFloatArraySIMD(fA, GROW, valueA, ZERO);
		//initFloatArraySIMD(fB, GROW, valueB, ZERO);

		//initFloatArray(fA, GROW, valueA, ZERO);
		//initFloatArray(fB, GROW, valueB, ZERO);
		break;
default:
		break;
	}
}

void initVectorFloatAB(vecm *vA, vecm *vB, int mode, int valueA, int valueB) {
	switch (mode) {
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
