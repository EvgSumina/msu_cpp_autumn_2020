all: test
test: allocator.cpp main.cpp
	g++ -o allocator allocator.cpp main.cpp
	./allocator
clean:
	rm -rf *.o allocator
