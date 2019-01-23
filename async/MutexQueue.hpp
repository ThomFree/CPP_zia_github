/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** MutexQueue
*/

#pragma once
#include <mutex>
#include <queue>

namespace async {
	template <typename T> class MutexQueue {
		public:
			MutexQueue() = default;
			MutexQueue(const MutexQueue<T> &) noexcept = default;
			~MutexQueue() noexcept = default;
			MutexQueue<T> &operator=(const MutexQueue<T> &) noexcept = default;

		/*
		** Methods
		*/
		public:
			inline void push(const T &data) {
				std::unique_lock<std::mutex> uniqueLock(_push);
				_queue.push(data);
			}

			inline void pop() {
				std::unique_lock<std::mutex> uniqueLock(_pop);
				_queue.pop();
			}

			inline bool empty() {
				std::unique_lock<std::mutex> uniqueLock(_empty);
				return _queue.empty();
			}

			inline size_t size() {
				std::unique_lock<std::mutex> uniqueLock(_size);
				return _queue.size();
			}

			inline const T &front() {
				std::unique_lock<std::mutex> uniqueLock(_front);
				return _queue.front();
			}

		/*
		** Fields
		*/
		private:
			std::mutex _push;
			std::mutex _pop;
			std::mutex _empty;
			std::mutex _size;
			std::mutex _front;
			std::queue<T> _queue;
	};
}
