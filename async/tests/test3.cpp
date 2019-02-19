/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** test3
*/

#include <iostream>

#include "ThreadPool.hpp"

int main()
{
	ThreadPool tp;

	tp.post([]() { return 9; });



/*
class ITask {
public:
	virtual ~ITask() = default;

};

class Task : public ITask {
private:
	int (*_invoke)(void *) = nullptr;
	std::unique_ptr<void, void (*)(void*)> _ptr;

public:
	template<typename Type, typename DerefType = std::decay_t<Type>>
	Task(Type &&task) :
	_ptr(new DerefType(std::forward<Type>(task)), [](void *ptr) {
		delete static_cast<DerefType*>(ptr);
	}),
	_invoke([&](void *ptr) -> int {
		return task();
	})
	{
	}

	auto operator()() -> decltype(_invoke(_ptr.get()))
	{
		return _invoke(_ptr.get());
	}

	Task(const Task&) = delete;
	Task(Task&&) = default;
	Task &operator=(Task&&) = default;
	Task() = default;
	~Task() = default;

};

int main()
{
	std::queue<Task> queue;

	Task t([]() -> int { return 9; });

	std::cout << t() << std::endl;

/*	queue.push(std::move(Task([]() -> int { return 9; })));

	auto &ref = queue.front();

	auto res = ref();
	std::cout << res << std::endl;

	queue.pop();

*/	return 0;
}