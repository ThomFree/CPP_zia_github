/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Service
*/

#include <iostream>
#include "async/Service.hpp"

async::Service::Service(SafeQueue<Task*> &tasks, std::condition_variable &condVar, std::mutex &mutex)
	: _mutex(mutex), _condVar(condVar), _queue(tasks), _isIddle(false)
{
	_thread = std::make_shared<std::thread>(std::thread(std::bind(&Service::run, this)));
	_id = _thread->get_id();
}

void async::Service::run()
{
	while (!async::STOP_SERVICE) {
		{
			std::unique_lock<std::mutex> lock(_mutex);
			_isIddle = true;
			if (!_condVar.wait(lock, [&]{ return !_queue.safeEmpty() || async::STOP_SERVICE; }))
				break;
/*			if (!_condVar.wait_for(lock, std::chrono::seconds(SERVICE_LIFE_DURATION),
							[&]{ return !_queue.safeEmpty() || async::STOP_SERVICE;}))
				if (async::STOP_SERVICE && _queue.safeEmpty())
					break;
*/			_isIddle = false;
			if (_queue.safeEmpty())
				continue;
		}
		std::cout << "Size: " << _queue.safeSize() << " - Unpacking task" << std::endl;
		auto task = _queue.safeFront();

		_queue.safePop();
		auto result = (*task)();
		delete task;

		std::cout << "Task exited with status: " << result << std::endl;
	}
	std::cout << "Service " << _id << " terminated :" << std::boolalpha << async::STOP_SERVICE << std::endl;
}
