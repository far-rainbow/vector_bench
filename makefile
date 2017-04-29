CC=gcc
PROF='ftest-coverage -fprofile-arcs'

all: vectorbenchMP

vectorbenchMP: vectorbench.o init.o initSIMD.o initSIMDMP.o init_wrappers.o tests.o
	gcc -pg -fopenmp vectorbench.o init.o init_wrappers.o initSIMD.o initSIMDMP.o tests.o -o vectorbenchMP.exe

vectorbench.o: ./src/src/vectorbench.c
	$(CC) -fopenmp -I./src/include -c ./src/src/vectorbench.c
	
init.o: ./src/src/init.c
	$(CC) -fopenmp -I./src/include -c ./src/src/init.c -DOPENMP_ENABLE
	$(CC) -fopenmp -I./src/include -c ./src/src/init.c -DOPENMP_ENABLE -S -o init.s
	
init_wrappers.o: ./src/src/init_wrappers.c
	$(CC) -fopenmp -I./src/include -c ./src/src/init_wrappers.c
	$(CC) -fopenmp -I./src/include -c ./src/src/init_wrappers.c -S -o init_wrappers.s
	
initSIMD.o: ./src/src/initSIMD.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMD.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMD.c -S -o initSIMD.s

initSIMDMP.o: ./src/src/initSIMDMP.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMDMP.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMDMP.c -S -o initSIMDMP.s
	
tests.o: ./src/src/tests.c
	$(CC) -fopenmp -I./src/include -c ./src/src/tests.c
	$(CC) -fopenmp -I./src/include -c ./src/src/tests.c -S -o tests.s
	
#vectorbenchNATIVE:
#	$(CC) ./src/src/* -o vectorbenchNATIVE.exe -I./src/include

vectorbenchNATIVE_PROF:
	$(CC) ./src/src/vectorbench.c -pg -fmessage-length=0 -ftest-coverage -fprofile-arcs -o vectorbenchNATIVE_PROF.exe -I./src/include
	
vectorbenchMP_PROF:
	$(CC) ./src/src/vectorbench.c -pg -fopenmp -fmessage-length=0 -ftest-coverage -fprofile-arcs -o vectorbenchMP_PROF.exe -I./src/include -DOPENMP=1
	
clean:
	-rm ./*.exe ./*.o ./*.s ./*.gcda ./*.gcno ./*.out