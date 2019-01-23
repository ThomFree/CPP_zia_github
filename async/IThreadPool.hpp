/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** ThreadPool
*/

#pragma once

namespace async {
	class IThreadPool {
		public:
			virtual ~IThreadPool() noexcept = default;

		public:
			virtual void stop() = 0;
			virtual void makeService() = 0;
			virtual void post(const std::function<void()>&, bool noWaiting= true) = 0;

		private:
			virtual void _join() = 0;
			virtual unsigned int _nbActiveServices() const = 0;
	};
}