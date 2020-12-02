#include "thred_pool.hpp"


explicit ThreadPool::ThreadPool(size_t poolSize): is_working(true)
{
	for (size_t i = 0; i < poolSize; i++)
	{
		thread_vector.emplace_back([this]() 
		{
			while(true)
			{
				unique_lock <mutex> lock(queue_locker);
				thread_check.wait(lock, [this] {return !is_working || task_queue.empty();})
				if (!is_working && task_queue.empty())
					return;
				function <void()> task = move(task_queue.front());
				task_queue.pop();
				task();
			}
		}
	}
}


ThreadPool::~ThreadPool()
{
	is_working = false;
	thred_check.notify_all();
	for (thread &elem: thread_vector)
		elem.join();
}


template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
{
	using return_type = decltype(func(args...));
	auto future_task = make_shared<packaged_task<return_type()>>(
		packaged_task<return_type()>(bind(func, args)));
	future <return_type> result = future_task->get_future();
	unique_lock <mutex> lock(queue_locker);
	task_queue.emplace([future_task](){ (*future_task)(); });
	thred_check.notify_one();
	return result;
}
