#pragma once
#include <iostream>

using namespace std;

class Allocator
{
	char* allocator;
	size_t offset;
	size_t max_size;
	bool flag;

public:
	Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};
