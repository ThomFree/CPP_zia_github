/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** ThreadPool
*/

#include <iostream>
#include <algorithm>

#include "async/ThreadPool.hpp"

std::atomic<bool> async::STOP_SERVICE(false);

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

void async::ThreadPool::post(const std::function<int()> &task, bool noWaiting)
{
	if (noWaiting && _noServiceAvailable()) {
		for (uint32_t i = 0; i != HARDWARE_CONCURRENCY; i++)
			makeService();
	}

//	_queue.safePush(std::move(Task(task)));
	_queue.safePush(new 	Task(task));
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
	return nbActive;
}

void async::ThreadPool::stop()
{
	async::STOP_SERVICE = true;
	_condVar.notify_all();
}

void async::ThreadPool::makeService()
{
	_servicesVector.push_back(std::make_unique<Service>(_queue, _condVar, _mutex));
	_nbServices++;
}