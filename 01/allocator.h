#include <iostream>

using namespace std;

class Allocator
{
	char* allocator;
	size_t offset;
	size_t max_size;
	bool flag;

public:
	Allocator()
	{
		allocator = nullptr;
		flag = true;
		offset = 0;
	}

	void makeAllocator(size_t maxSize)
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

	char* alloc(size_t size)
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
		}
	}

    void reset()
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

	~Allocator()
	{
		if (allocator != nullptr)
			delete []allocator;
	}
};

