/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** AThreadPool
*/

#pragma once
#include <vector>
#include <functional>

#include "IThreadPool.hpp"
#include "Service.hpp"

namespace async {
	const unsigned int HARDWARE_CONCURRENCY = std::thread::hardware_concurrency();
	class ThreadPool : public IThreadPool {
		public:
			explicit ThreadPool(size_t size = HARDWARE_CONCURRENCY);
			ThreadPool(const ThreadPool &) noexcept = default;
			~ThreadPool() noexcept;
			ThreadPool &operator=(ThreadPool &) noexcept = default;

		/*
		** Methods
		*/
		public:
			void stop() override;
			void post(const std::function<void()> &task, bool noWaiting = true) override;
			void makeService() override;
			inline size_t getNbServ() { return _queue.size(); };

		private:
			void _join() override;
			unsigned int _nbActiveServices() const override;
			inline bool _noServiceAvailable() const { return _nbActiveServices() == _nbServices; }

		/*
		** Fields
		*/
		private:
			std::vector<std::unique_ptr<Service>> _servicesVector;
			MutexQueue<std::function<void()>> _queue;
			std::condition_variable _condVar;
			std::mutex _mutex;
			uint32_t _nbServices;
	};
}