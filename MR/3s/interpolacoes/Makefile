mylib=-L . -lTrab2
rootlibs=`root-config --cflags` -L `root-config --libdir` -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGpad -lTree -lRint -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic
objects3=DataInterpolator.o cFCgraphics.o EqSolver.o cFCgraphics.o
objects2=EqSolver.o cFCgraphics.o
objects4=Decay.o Element.o PhysProcess.o BetaDecay.o cFCgraphics.o

help:
	@echo "run:\n\n\t\"make decay\" to compile Decay.C program\n\n\t\"make Springs\"to compile Springs.C program\n\n\t\"make Interpolator\" to compile mainInterpolator.C program\n\n\t\"make tex\" to produce pdf report\n\n\t\"make clean\" to delete .o files\n"     
result:lib3Trab2.a main_result.o
	g++ -o main_result.exe main_result.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file main_result.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./main_result.exe "\n\n"  
	@echo  "          (__) \n          (oo) \n    /------\/ \n   / |    || \n*    /\---/\ \n     ~~   ~~ "
main_result.o: main_result.C cFCgraphics.h
	g++ -c main_result.C $(rootlibs)
DataInterpolator.o: DataInterpolator.C DataInterpolator.h
	g++ -c DataInterpolator.C $(rootlibs)
cFCgraphics.o: cFCgraphics.C cFCgraphics.h
	g++ -c cFCgraphics.C $(rootlibs)
lib2Trab2.a:$(objects2)
	ar ruv libTrab2.a $^
	ranlib libTrab2.a
lib3Trab2.a:$(objects3)
	ar ruv libTrab2.a $^
	ranlib libTrab2.a
lib4Trab2.a:$(objects4)
	ar ruv libTrab2.a $^
	ranlib libTrab2.a
clean:
	rm -f *.a *.o
