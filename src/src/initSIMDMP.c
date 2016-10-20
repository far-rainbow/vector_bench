#include <def.h>

// valueB is not used. future feature stub
#pragma omp declare simd
void initFloatArraySIMDMP(float *fA, int initMode, int valueA, int valueB) {

	int i;
	float n;

	switch (initMode) {
	case INT:
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			fA[i] = (float) valueA;
		}
		break;
	case GROW:

#pragma omp parallel shared(fA) private(i,n)
{
		n = (float)(omp_get_thread_num()+1.1)/10 + valueA;
#pragma omp for
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			fA[i] = i+n;
		}
}
		break;
	default:
		break;
	}
}
