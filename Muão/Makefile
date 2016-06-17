mylib=-L . -lTrab2
rootlibs=`root-config --cflags` -L `root-config --libdir` -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGpad -lTree -lRint -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic

help:
	@echo "run:\n\n\t\"make graphs\" to compile graphs.C program\n\n\n"     
graphs:lib3Trab2.a graphs.o
	g++ -o graphs.exe graphs.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./graphs.exe "\n\n" 
hist:lib3Trab2.a hist.o
	g++ -o hist.exe hist.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist.exe "\n\n" 
hist+-:lib3Trab2.a hist+-.o
	g++ -o hist+-.exe hist+-.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist+-.exe "\n\n" 
hist_loop:lib3Trab2.a hist_loop.o
	g++ -o hist_loop.exe hist_loop.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist_loop.exe "\n\n" 
hist_loop+-:lib3Trab2.a hist_loop+-.o
	g++ -o hist_loop+-.exe hist_loop+-.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist_loop+-.exe "\n\n" 
range:lib3Trab2.a Range.o
	g++ -o Range.exe Range.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./Range.exe "\n\n" 
Range.o: Range.C
	g++ -c Range.C $(rootlibs)
graphs.o: graphs.C 
	g++ -c graphs.C $(rootlibs)
hist.o: hist.C 
	g++ -c hist.C $(rootlibs)
hist+-.o: hist+-.C 
	g++ -c hist+-.C $(rootlibs)
hist_loop+-.o: hist_loop+-.C 
	g++ -c hist_loop+-.C $(rootlibs)
hist_loop.o: hist_loop.C 
	g++ -c hist_loop.C $(rootlibs)
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
