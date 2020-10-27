CFLAGS = -std=c++1z -Wall -Werror -c -ggdb3

all: prog

test:
	./prog

prog: tests.o matrix.o
	g++ tests.o matrix.o -o prog
parser.o: matrix.cpp
	g++ $(CFLAGS) matrix.cpp -o matrix.o
tests.o: tests.cpp
	g++ $(CFLAGS) tests.cpp -o tests.o
clean:
	rm -rf *.o prog
	rm -rf *.exe prog
