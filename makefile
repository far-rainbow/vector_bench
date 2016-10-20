CC=gcc

all: vectorbenchMP

vectorbenchMP: test.o init.o initSIMD.o initSIMDMP.o init_wrappers.o
	gcc -fopenmp test.o init.o initSIMD.o initSIMDMP.o init_wrappers.o -o vectorbenchMP.exe

test.o: ./src/src/test.c
	$(CC) -fopenmp -I./src/include -c ./src/src/test.c
	
init.o: ./src/src/init.c
	$(CC) -fopenmp -I./src/include -c ./src/src/init.c -DOPENMP_ENABLE
	$(CC) -fopenmp -I./src/include -c ./src/src/init.c -DOPENMP_ENABLE -S -o init.s
	
init_wrappers.o: ./src/src/init_wrappers.c
	$(CC) -fopenmp -I./src/include -c ./src/src/init_wrappers.c
	$(CC) -fopenmp -I./src/include -c ./src/src/init_wrappers.c -S -o init_wrappers.s
	
initSIMD.o: ./src/src/initSIMD.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMD.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMD.c -S -o initSIMD.s

initSIMDMP.o: ./src/src/initSIMD.c	
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMDMP.c
	$(CC) -fopenmp -I./src/include -c ./src/src/initSIMDMP.c -S -o initSIMDMP.s
	
#vectorbenchNATIVE:
#	$(CC) ./src/src/* -o vectorbenchNATIVE.exe -I./src/include

vectorbenchNATIVE_PROF:
	$(CC) ./src/src/test.c -pg -fmessage-length=0 -ftest-coverage -fprofile-arcs -o vectorbenchNATIVE_PROF.exe -I./src/include
	
vectorbenchMP_PROF:
	$(CC) ./src/src/test.c -pg -fopenmp -fmessage-length=0 -ftest-coverage -fprofile-arcs -o vectorbenchMP_PROF.exe -I./src/include -DOPENMP=1
	
clean:
	-rm ./*.exe ./*.o ./*.s