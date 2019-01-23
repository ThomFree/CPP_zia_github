/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** ThreadPool
*/

#include <iostream>
#include <algorithm>

#include "async/ThreadPool.hpp"

async::ThreadPool::ThreadPool(size_t servicesCount)
	: _nbServices(0)
{
	for (; servicesCount > 0; servicesCount--)
		makeService();
}

async::ThreadPool::~ThreadPool()
{
	stop();
	_join();
}

void async::ThreadPool::post(const std::function<void()> &task, bool noWaiting)
{
	if (noWaiting && _noServiceAvailable()) {
		for (uint32_t i = 0; i != HARDWARE_CONCURRENCY; i++)
			makeService();
	}
	_queue.push(task);
	_condVar.notify_one();
};

void async::ThreadPool::_join()
{
	std::for_each(_servicesVector.begin(), _servicesVector.end(), [](std::unique_ptr<Service> &s) {
		if (s->joinable())
			s->join();
	});
}

uint32_t async::ThreadPool::_nbActiveServices() const
{
	uint32_t nbActive = 0;

	for (auto &it : _servicesVector) {
		if (!it->isIddle())
			nbActive++;
	}
	std::cout << nbActive << " " << _nbServices << std::endl;
	return nbActive;
}

void async::ThreadPool::stop()
{
	std::for_each(_servicesVector.begin(), _servicesVector.end(), [](std::unique_ptr<Service> &s) { s->setStop(true); });
	_condVar.notify_all();
}

void async::ThreadPool::makeService()
{
	_servicesVector.push_back(std::make_unique<Service>(_queue, _condVar, _mutex));
	_nbServices++;
}