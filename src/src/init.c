#include "test.h"

#ifdef OPENMP_ENABLE
//#define OPENMP
#endif

// valueB is not used. future feature stub
void initFloatArray(float *fA, int initMode, int valueA, int valueB) {

	int i;
	float n = (float)valueA;

	switch (initMode) {
	case INT:
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			fA[i] = (float) valueA;
		}
		break;
	case GROW:

#ifdef OPENMP
#pragma omp parallel shared(fA) private(i,n)
{
		n = (float)(omp_get_thread_num()+1.1)/10;

		#pragma omp for
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			//fA[i] = (float) valueA++ / 3.14159;
			fA[i] = i+n;
		}
}
#else
		n = 0.777777;
		for (i = 0; i < FLOAT_ARRAY_SIZE; i++) {
			//fA[i] = (float) valueA++ / 3.14159;
			fA[i] = n++;
		}
#endif

		break;
	default:
	break;
	}
}

// valueB is not used. future feature stub
void initVectorArray(vecm *vA, int initMode, int valueA, int valueB) {

	int i, j;
	float n;
	float *vfA;

	switch (initMode) {
	case INT:
		for (i = 0; i < VECTOR_ARRAY_SIZE; i++) {
			vfA = (float *) &vA[i];
			for (j = 0; j < VECTORSIZE; j++) {
				vfA[j] = valueA;
			}
		}
		break;
	case GROW:

#ifdef OPENMP
#pragma omp parallel shared(vA) private(i,n) /* add vfA into private vars to use slow pointer loop */
{
		// rational part as thread tag
		n = (float)(omp_get_thread_num()+1.1)/10;

		#pragma omp for
		for (i = 0; i < VECTOR_ARRAY_SIZE; i++) {

			// slower
			//vA[i] = (vecm){i<<2,(i<<2)+1,(i<<2)+2,(i<<2)+3} + (vecm){n,n,n,n};

			// faster
			vA[i] = (vecm){(i<<2)+n,(i<<2)+1+n,(i<<2)+2+n,(i<<2)+3+n};
		}
}
#else
		n = 0.777777;
		for (i = 0; i < VECTOR_ARRAY_SIZE; i++) {
			// slower
			//vA[i] = (vecm){i<<2,(i<<2)+1,(i<<2)+2,(i<<2)+3} + (vecm){n,n,n,n};

			// faster
			vA[i] = (vecm){(i<<2)+n,(i<<2)+1+n,(i<<2)+2+n,(i<<2)+3+n};
		}
#endif

		break;
	default:
		break;
	}
}
