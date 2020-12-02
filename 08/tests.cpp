#include "thread_pool.hpp"
#include <iostream>

struct A {
	int a = 3;
};

void foo(const A&) {}

int main() {

	ThreadPool pool(8);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 1; });
	task2.get();
	
	std::cout << "Success" << std::endl;
	return 0;
}
