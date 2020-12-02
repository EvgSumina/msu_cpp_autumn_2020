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
	condition_variable thread_check;
	mutex queue_locker;

public:
	explicit ThreadPool(size_t poolSize)
	{
		for (size_t i = 0; i < poolSize; i++)
		{
			thread_vector.emplace_back([this]() 
			{
				while(true)
				{
					unique_lock <mutex> lock(queue_locker);
					if (!task_queue.empty())
					{
						function <void()> task = move(task_queue.front());
						task_queue.pop();
						lock.unlock();
						task();
					}
					else
					{
						if (!is_working)
							thread_check.wait(lock);
						else
							break;
					}
					
				}
			});
		}
	}

	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> future<decltype(func(args...))>
	{
		using result_type = decltype(func(args...));
		auto future_task = make_shared<packaged_task<result_type()>>(packaged_task<result_type()>(move(bind(func, args...))));
		unique_lock <mutex> lock(queue_locker);
		task_queue.emplace([future_task](){ (*future_task)(); });
		thread_check.notify_one();
		return future_task->get_future();
	}

	~ThreadPool()
	{
		is_working = false;
		thread_check.notify_all();
		for (thread &elem: thread_vector)
			elem.join();
	}
};
