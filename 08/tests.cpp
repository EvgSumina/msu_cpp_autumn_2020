#include "thread_pool.hpp"
#include <iostream>
#define NUM_THREADS 5
#include <cassert>

struct A {};

void foo(const A&) {}

int sum(const vector<int>& v, size_t begin, size_t end) {
	int result = 0;
	for (size_t i = begin; i < end; ++i) 
	{
		result += v[i];
	}
	return result;
};

int main() 
{
	ThreadPool pool(2);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 1; });
	task2.get();

	ThreadPool new_pool(NUM_THREADS);
	vector<int> vect(10000, 1);
	vector<future<int>> futures;

	for (size_t i = 0; i < vect.size(); i += vect.size() / NUM_THREADS)
		futures.push_back(new_pool.exec(sum, vect, i, i + vect.size() / NUM_THREADS));

	int thread_sum = 0;
	for (future<int>& elem: futures)
		thread_sum += elem.get();

	assert(sum(vect, 0, vect.size()) == thread_sum);
	std::cout << "Success!" << std::endl;
	return 0;
}
