CFLAGS = -std=c++1z -Wall -Werror -c -ggdb3

all: prog

test:
	./prog

prog: main.o allocator.o
	g++ main.o allocator.o -o prog
allocator.o: allocator.cpp
	g++ $(CFLAGS) allocator.cpp -o allocator.o
main.o: main.cpp
	g++ $(CFLAGS) main.cpp -o main.o
clean:
	rm -rf *.o prog
