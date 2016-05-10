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


4:lib3Trab2.a main_result_SV3_4.o file_reader.o
	g++ -o main_result_SV3_4.exe main_result_SV3_4.o file_reader.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file main_result_SV3_4.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./main_result_SV3_4.exe "\n\n" 
4400:lib3Trab2.a 400_SV3_4.o
	g++ -o 400_SV3_4.exe 400_SV3_4.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file 400_SV3_4.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./400_SV3_4.exe "\n\n"

2:lib3Trab2.a main_result_SV3_2.o file_reader.o
	g++ -o main_result_SV3_2.exe main_result_SV3_2.o file_reader.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file main_result_SV3_2.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./main_result_SV3_2.exe "\n\n" 
2400:lib3Trab2.a 400_SV3_2.o 
	g++ -o 400_SV3_2.exe 400_SV3_2.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file 400_SV3_2.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./400_SV3_2.exe "\n\n" 

B:lib3Trab2.a main_result_SV4B.o file_reader.o
	g++ -o main_result_SV4B.exe main_result_SV4B.o file_reader.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file main_result_SV4B.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./main_result_SV4B.exe "\n\n" 
B400:lib3Trab2.a 400_SV4_B.o
	g++ -o 400_SV4_B.exe 400_SV4_B.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file 400_SV4_B.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./400_SV4_B.exe "\n\n" 

D:lib3Trab2.a main_result_SV4D.o file_reader.o
	g++ -o main_result_SV4D.exe main_result_SV4D.o file_reader.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file main_result_SV4D.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./main_result_SV4D.exe "\n\n" 
D400:lib3Trab2.a 400_SV4_D.o
	g++ -o 400_SV4_D.exe 400_SV4_D.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file 400_SV4_D.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./400_SV4_D.exe "\n\n" 

graphs:lib3Trab2.a MR_graphs.o
	g++ -o MR_graphs.exe MR_graphs.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./MR_graphs.exe "\n\n" 
qui_graphs:lib3Trab2.a qui_graphs.o
	g++ -o qui_graphs.exe qui_graphs.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./qui_graphs.exe "\n\n" 
MR_graphs.o: MR_graphs.C 
	g++ -c MR_graphs.C $(rootlibs)
qui_graphs.o: qui_graphs.C
	g++ -c qui_graphs.C $(rootlibs)
main_result_SV3_4.o: main_result_SV3_4.C 
	g++ -c main_result_SV3_4.C $(rootlibs)
400_SV3_4.o: 400_SV3_4.C
	g++ -c 400_SV3_4.C $(rootlibs)

main_result_SV3_2.o: main_result_SV3_2.C
	g++ -c main_result_SV3_2.C $(rootlibs)
400_SV3_2.o: 400_SV3_2.C
	g++ -c 400_SV3_2.C $(rootlibs)

main_result_SV4B.o: main_result_SV4B.C 
	g++ -c main_result_SV4B.C $(rootlibs)
400_SV4_B.o: 400_SV4_B.C
	g++ -c 400_SV4_B.C $(rootlibs)

main_result_SV4D.o: main_result_SV4D.C 
	g++ -c main_result_SV4D.C $(rootlibs)
400_SV4_D.o: 400_SV4_D.C
	g++ -c 400_SV4_D.C $(rootlibs)



file_reader.o: file_reader.C
	g++ -c file_reader.C

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
