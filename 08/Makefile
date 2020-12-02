CFLAGS = -c -Wall -Werror -std=c++1z

all: my_prog

test:
	./my_prog

my_prog: tests.o
	g++ -o my_prog tests.o

tests.o: tests.cpp thread_pool.hpp
	g++ $(CFLAGS) tests.cpp

clean:
	rm -rf *.o my_prog
	rm -rf *.stackdump my_prog
	rm -rf *.exe my_prog
