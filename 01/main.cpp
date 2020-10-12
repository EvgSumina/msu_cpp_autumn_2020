#include <iostream>
#include "allocator.h"

using namespace std;

void test_1()
{
	Allocator allocator;
	allocator.makeAllocator(sizeof(char) * 10);
	char* memory_1 = allocator.alloc(sizeof(char) * 5);
	char* memory_2 = allocator.alloc(sizeof(char) * 5);
	allocator.reset();
}

void test_2()
{
	Allocator allocator;
	allocator.makeAllocator(sizeof(char) * 10);
	allocator.makeAllocator(sizeof(char) * 10);
}

void test_3()
{
	Allocator allocator;
	char* memory_1 = allocator.alloc(sizeof(char) * 5);
}

void test_4()
{
	Allocator allocator;
	allocator.reset();
}

void test_5()
{
	Allocator allocator;
	allocator.makeAllocator(sizeof(char) * 10);
	char* memory_1 = allocator.alloc(sizeof(char) * 5);
	allocator.reset();
	char* memory_2 = allocator.alloc(sizeof(char) * 5);
}

int main()
{
	cout << "Test_1 \n";
	test_1();
	cout << "Test_1 is OK \n\n";

	cout << "Test_2 \n";
	test_2();
	cout << "Test_2 is not OK \n\n";

	cout << "Test_3 \n";
	test_3();
	cout << "Test_3 is not OK \n\n";

	cout << "Test_4 \n";
	test_4();
	cout << "Test_4 is not OK \n\n";

	cout << "Test_5 \n";
	test_5();
	cout << "Test_5 is OK \n\n";
	return 0;
}
