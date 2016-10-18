all: vectorbenchMP vectorbenchNATIVE vectorbenchNATIVE_PROF vectorbenchNATIVE_O0 vectorbenchNATIVE_O1 vectorbenchNATIVE_O2 vectorbenchNATIVE_O3

vectorbenchMP:
	gcc ./src/src/test.c -fopenmp -o vectorbenchMP.exe -I./src/include -DOPENMP=1

vectorbenchNATIVE:
	gcc ./src/src/test.c -o vectorbenchNATIVE.exe -I./src/include

vectorbenchNATIVE_O3:
	gcc ./src/src/test.c -o vectorbenchNATIVE_O3.exe -I./src/include -O3
	
vectorbenchNATIVE_O2:
	gcc ./src/src/test.c -o vectorbenchNATIVE_O2.exe -I./src/include -O2
	
vectorbenchNATIVE_O1:
	gcc ./src/src/test.c -o vectorbenchNATIVE_O1.exe -I./src/include -O1
	
vectorbenchNATIVE_O0:
	gcc ./src/src/test.c -o vectorbenchNATIVE_O0.exe -I./src/include -O0
	
vectorbenchNATIVE_PROF:
	gcc ./src/src/test.c -pg -fmessage-length=0 -ftest-coverage -fprofile-arcs -o vectorbenchNATIVE_PROF.exe -I./src/include
	
vectorbenchMP_PROF:
	gcc ./src/src/test.c -pg -fopenmp -fmessage-length=0 -ftest-coverage -fprofile-arcs -o vectorbenchMP_PROF.exe -I./src/include
	
clean:
	-rm ./*.exe