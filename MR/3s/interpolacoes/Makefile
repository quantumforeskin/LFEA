mylib=-L . -lTrab2
rootlibs=`root-config --cflags` -L `root-config --libdir` -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGpad -lTree -lRint -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic
objects3=DataInterpolator.o cFCgraphics.o EqSolver.o cFCgraphics.o
objects2=EqSolver.o cFCgraphics.o
objects4=Decay.o Element.o PhysProcess.o BetaDecay.o cFCgraphics.o

help:
	@echo "run:\n\n\t\"make decay\" to compile Decay.C program\n\n\t\"make Springs\"to compile Springs.C program\n\n\t\"make Interpolator\" to compile mainInterpolator.C program\n\n\t\"make tex\" to produce pdf report\n\n\t\"make clean\" to delete .o files\n"     
tex:
	pdflatex groupB11Trab2.tex
	evince groupB11Trab2.pdf &
Interpolator:lib3Trab2.a mainInterpolator.o
	g++ -o mainInterpolator.exe mainInterpolator.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file mainInterpolator.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./mainInterpolator.exe "\n\n"  
	@echo  "          (__) \n          (oo) \n    /------\/ \n   / |    || \n*    /\---/\ \n     ~~   ~~ "
mainInterpolator.o: mainInterpolator.C cFCgraphics.h
	g++ -c mainInterpolator.C $(rootlibs)
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
