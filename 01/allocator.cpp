#include <iostream>
#include "allocator.h"

using namespace std;

	Allocator::Allocator()
	{
		allocator = nullptr;
		flag = true;
		offset = 0;
	}

	void Allocator::makeAllocator(size_t maxSize)
	{
		try
		{
			if (flag)
			{
				allocator = new char[maxSize];
				max_size = maxSize;
				flag = false;
			}
			else
			{
				throw "I have already allocate\n";
			}
		}

		catch (char const* str)
		{
			cout << str;
		}
	}

	char* Allocator::alloc(size_t size)
	{
		try
		{
			if (flag)
			{
				throw "Allocate at first\n";
			}
			if ((size + offset) <= max_size)
			{
				offset += size;
				return (allocator + offset - size);
			}
			return nullptr;
		}

		catch (char const* str)
		{
			cout << str;
			return nullptr;
		}
	}

	void Allocator::reset()
	{
		try
		{
			if (flag)
			{
				throw "Allocate,then reset\n";
			}
			offset = 0;
		}

		catch (char const* str)
		{
			cout << str;
		}
	};

	Allocator::~Allocator()
	{
		if (allocator != nullptr)
			delete []allocator;
	}

