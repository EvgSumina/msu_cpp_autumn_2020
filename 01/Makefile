CC=g++
CFLAGS = -std=c++1z -Wall -Werror -c -ggdb3

all: allocator

allocator: main.o allocator.o
	$(CC) main.o allocator.o -o allocator
allocator.o: allocator.cpp
	$(CC) $(CFLAGS) allocator.cpp -o allocator.o
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o
clean:
	rm -rf *.o allocator
