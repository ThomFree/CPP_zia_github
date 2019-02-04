/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Service
*/

#include <iostream>
#include "async/Service.hpp"

async::Service::Service(MutexQueue<std::function<void()>> &tasks, std::condition_variable &condVar, std::mutex &mutex)
	: _mutex(mutex), _condVar(condVar), _queue(tasks), _isIddle(false)
{
	_thread = std::make_shared<std::thread>(std::thread(std::bind(&Service::run, this)));
	_id = _thread->get_id();
}

void async::Service::run()
{
	std::function<void()> task;
	while (!async::STOP_SERVICE) {
		{
			std::unique_lock<std::mutex> lock(_mutex);
			_isIddle = true;
			if (!_condVar.wait_for(lock, std::chrono::seconds(SERVICE_LIFE_DURATION),
							  [&]{ return !_queue.empty() || async::STOP_SERVICE;}))
				break;
			_isIddle = false;
			if (_queue.empty())
				continue;
			task = _queue.front();
			_queue.pop();
		}
		task();
	}
	std::cout << "Service " << _id << " terminated :" << std::boolalpha << async::STOP_SERVICE << std::endl;
}