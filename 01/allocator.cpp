#include <iostream>
#include "allocator.h"

using namespace std;

	Allocator::Allocator()
	{
		allocator = nullptr;
		offset = 0;
		max_size = 0;
	}

	void Allocator::makeAllocator(size_t maxSize)
	{
		if (allocator)
		{
			delete []allocator;
		}
		allocator = new char[maxSize / sizeof(char)];
		max_size = maxSize;
		offset = 0;
	}

	char* Allocator::alloc(size_t size)
	{
		if ((size + offset) <= max_size)
		{
			offset += size;
			return (allocator + (offset - size) / sizeof(char));
		}
		return nullptr;
	}

	void Allocator::reset()
	{
		offset = 0;
	}

	Allocator::~Allocator()
	{
		if (allocator != nullptr)
			delete []allocator;
			allocator = nullptr;
	}

