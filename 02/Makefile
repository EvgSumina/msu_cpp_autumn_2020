CFLAGS = -std=c++1z -Wall -Werror -c -ggdb3

all: prog

test:
	./prog

prog: tests.o parser.o
	g++ tests.o parser.o -o prog
parser.o: parser.cpp
	g++ $(CFLAGS) parser.cpp -o parser.o
tests.o: tests.cpp
	g++ $(CFLAGS) tests.cpp -o tests.o
clean:
	rm -rf *.o prog
