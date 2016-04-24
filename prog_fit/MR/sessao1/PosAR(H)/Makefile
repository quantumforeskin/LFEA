# $@    Nome da regra. 
# $<    Nome da primeira dependência 
# $^     Lista de dependências
# $?     Lista de dependências mais recentes que a regra.
# $*     Nome do arquivo sem sufixo

# Global Variable Declarations
CC= g++
FCLIB= -I ../../../LIBs

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`


##ex2
SRC2= plots.C
OBJ2= $(SRC2:.C=.o)
EXE2= plots.exe


##Routines
all: Plot

## .o generator
%.o:%.C 
	@echo Installing Virus...
	$(CC)  -c  $(CFLAGS) $(FCLIB)   $<  -o $@ 

Plot: plots.exe
$(EXE2): $(OBJ2)
	$(CC) -o $@ $(OBJ2) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...
	@./plots.exe	


clean:
	rm -rf *~ *.o $(EXE2)
