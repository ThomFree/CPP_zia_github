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

#include "IService.hpp"
#include "MutexQueue.hpp"

namespace async {
	const size_t SERVICE_LIFE_DURATION = 60;
	class Service : public IService {
		public:
			Service(MutexQueue<std::function<void()>> &, std::condition_variable &, std::mutex&);
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
			inline void setStop(bool status) override { *_stop = status; }
			inline bool isIddle() const noexcept override { return _isIddle; }

		private:
			void run() override;

		/*
		** Fields
		*/
		private:
			std::mutex &_mutex;
			std::condition_variable &_condVar;
			MutexQueue<std::function<void()>> &_queue;
			std::shared_ptr<std::atomic_bool> _stop;
			std::thread::id _id;
			std::shared_ptr<std::thread> _thread;
			bool _isIddle;
	};
}
