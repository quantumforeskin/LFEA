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
hist+-_new:lib3Trab2.a hist+-_new.o
	g++ -o hist+-_new.exe hist+-_new.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist+-_new.exe "\n\n" 
hist+-cap:lib3Trab2.a hist+-cap.o
	g++ -o hist+-cap.exe hist+-cap.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist+-cap.exe "\n\n" 
hist+-cap_new:lib3Trab2.a hist+-cap_new.o
	g++ -o hist+-cap_new.exe hist+-cap_new.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist+-cap_new.exe "\n\n" 
hist_loop:lib3Trab2.a hist_loop.o
	g++ -o hist_loop.exe hist_loop.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist_loop.exe "\n\n" 
hist_loop+-:lib3Trab2.a hist_loop+-.o
	g++ -o hist_loop+-.exe hist_loop+-.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist_loop+-.exe "\n\n" 
hist_loop+-_new:lib3Trab2.a hist_loop+-_new.o
	g++ -o hist_loop+-_new.exe hist_loop+-_new.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist_loop+-_new.exe "\n\n" 
hist_loop+-cap:lib3Trab2.a hist_loop+-cap.o
	g++ -o hist_loop+-cap.exe hist_loop+-cap.o $(mylib) $(rootlibs)
	@echo "\n\n" The executable file teste.exe has been created "\n\n                " to execute run on terminal:"\n                               " ./hist_loop+-cap.exe "\n\n" 
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
hist+-_new.o: hist+-_new.C 
	g++ -c hist+-_new.C $(rootlibs)
hist+-cap.o: hist+-cap.C 
	g++ -c hist+-cap.C $(rootlibs)
hist+-cap_new.o: hist+-cap_new.C 
	g++ -c hist+-cap_new.C $(rootlibs)
hist_loop+-.o: hist_loop+-.C 
	g++ -c hist_loop+-.C $(rootlibs)
hist_loop+-_new.o: hist_loop+-_new.C 
	g++ -c hist_loop+-_new.C $(rootlibs)
hist_loop+-cap.o: hist_loop+-cap.C 
	g++ -c hist_loop+-cap.C $(rootlibs)
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
