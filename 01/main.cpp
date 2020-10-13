#include <iostream>
#include "allocator.h"
#include <cassert>

using namespace std;

void test_1()
{
	Allocator allocator;
	allocator.makeAllocator(sizeof(char) * 10);
	assert(nullptr != allocator.alloc(10 * sizeof(char)));
	assert(nullptr == allocator.alloc(1 * sizeof(char)));
	allocator.reset();
	assert(nullptr != allocator.alloc(5 * sizeof(char)));
	assert(nullptr != allocator.alloc(5 * sizeof(char)));
	assert(nullptr == allocator.alloc(1 * sizeof(char)));
}

void test_2()
{
	Allocator allocator;
	allocator.makeAllocator(10 * sizeof(char));
	assert(nullptr == allocator.alloc(11 * sizeof(char)));
	assert(nullptr != allocator.alloc(5 * sizeof(char)));
	assert(nullptr != allocator.alloc(5 * sizeof(char)));
	assert(nullptr == allocator.alloc(1 * sizeof(char)));
}

int main()
{
	test_1();
	test_2();
	return 0;
}
