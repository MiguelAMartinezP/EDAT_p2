CC = gcc
CFLAGS = -Wall -pedantic -ansi
LDLIBS = -lodbc

EXE = menu

all: $(EXE)

clean:
	rm -f *.o core $(EXE)

$(EXE): %: %.o odbc.o orders.o customers.o products.o

splint:
	splint -nullpass *.c *.h > splint.log