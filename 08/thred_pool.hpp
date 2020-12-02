#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>


using namespace std;


class ThreadPool
{
	vector <thread> thread_vector;
	queue <function <void()>> task_queue;
	atomic <bool> is_working;
	condition_variable thred_check;
	mutex queue_locker;

public:
	explicit ThreadPool(size_t poolSize);

	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> future<decltype(func(args...))>;
	~ThreadPool();
};



