all: jCbc.dll   Example2 Example1

Cbc_Path="C:/Office/MILP/Cbc-2.9.8"
Cflag=-DHAVE_STRUCT_TIMESPEC




jCbc.o:jCbc.cpp   Makefile
	g++ -fopenmp -fPIC -c jCbc.cpp  -static -Wl,--kill-at $(Cflag)   -I $(Cbc_Path)/include/coin 

jCbc.dll:jCbc.o Makefile
	g++ -fopenmp -fPIC -shared *.o -o jCbc.dll  -I  $(Cbc_Path)/include/coin -L    $(Cbc_Path)/lib  -lCbcSolver -lCbc  -lClp -lOsiClp -lOsi -lOsiCbc -lCgl -lCoinUtils -lcoinmumps -lcoinblas -lcoinlapack -lcoinasl -lcoinmetis -lcoinglpk -lgfortran -lz -lquadmath -lpthread



Example1: jCbc.dll  Makefile Example1.cpp
	g++ -fopenmp -fPIC    -o Example1  jCbc.dll Example1.cpp -I  $(Cbc_Path)/include/coin   


Example2: jCbc.dll  Makefile Example2.cpp
	g++ -fopenmp -fPIC    -o Example2  jCbc.dll Example2.cpp -I  $(Cbc_Path)/include/coin   
