#include "test.h"

// valueB is not used. future feature stub
#pragma omp declare simd
void initFloatArraySIMD(float *fA, int initMode, int valueA, int valueB) {

	int i;
	float n = (float)valueA;

	switch (initMode) {
	case INT:
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			fA[i] = (float) valueA;
		}
		break;
	case GROW:

		n = (float)(omp_get_thread_num()+1.1)/1;

		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			//fA[i] = (float) valueA++ / 3.14159;
			fA[i] = i+n;
		}
		break;
	default:
		break;
	}
}
