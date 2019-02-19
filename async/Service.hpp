/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** Service
*/

#pragma once
#include <functional>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <future>
#include <type_traits>
#include <utility>

#include "IService.hpp"
#include "SafeQueue.hpp"
#include "Task.hpp"

namespace async {
	extern std::atomic<bool> STOP_SERVICE;
	const size_t SERVICE_LIFE_DURATION = 60;

	class Service : public IService {
		public:
			Service(SafeQueue<Task*> &, std::condition_variable &, std::mutex&);
			Service(const Service &) noexcept = default;
			~Service() noexcept = default;
			Service &operator=(const Service &) noexcept = default;

		/*
		** Methods
		*/
		public:
			inline bool joinable() const override { return _thread->joinable(); }
			inline void join() const override { _thread->join(); }
			inline const std::thread::id &getId() const noexcept override { return _id; }
			inline bool isIddle() const noexcept override { return _isIddle; }

		private:
			void run() override;

		/*
		** Fields
		*/
		private:
			std::mutex &_mutex;
			std::condition_variable &_condVar;
			//SafeQueue<Task> &_queue;
			SafeQueue<Task*> &_queue;
			std::thread::id _id;
			std::shared_ptr<std::thread> _thread;
			bool _isIddle;
	};
}
