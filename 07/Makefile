CFLAGS = -c -Wall -Werror -std=c++1z

all: my_prog

test:
	./my_prog

my_prog: tests.o
	g++ tests.o -o my_prog

tests.o: tests.cpp
	g++ $(CFLAGS) tests.cpp -o tests.o

clean:
	rm -rf *.o my_prog
	rm -rf *.stackdump my_prog
	rm -rf *.exe my_prog
