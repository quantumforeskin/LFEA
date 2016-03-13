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
SRC2= fitter.C
OBJ2= $(SRC2:.C=.o)
EXE2= fitter.exe

SRC3= main.C Opt.C
OBJ3= $(SRC3:.C=.o)
EXE3= main.exe

SRC4= calib.C
OBJ4= $(SRC4:.C=.o)
EXE4= calib.exe


##Routines
all: Fit

## .o generator
%.o:%.C 
	@echo Installing Virus...
	$(CC)  -c  $(CFLAGS) $(FCLIB)   $<  -o $@ 

FitExe: fitter.exe
	@./fitter.exe	

Fitter: $(OBJ2)
	$(CC) -o $(EXE2) $(OBJ2) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...

Fit: $(OBJ3)
	$(CC) -o $(EXE3) $(OBJ3) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...

Teste: $(OBJ4)
	$(CC) -o $(EXE4) $(OBJ4) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...




clean:
	rm -rf *~ *.o $(EXE2)
