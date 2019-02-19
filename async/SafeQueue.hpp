/*
** EPITECH PROJECT, 2018
** Zia
** File description:
** SafeQueue
*/

#pragma once
#include <mutex>
#include <queue>
#include <type_traits>

namespace async {
	template<typename T, typename Container = std::deque<T>>
	class SafeQueue : public std::queue<T, Container> {
		public:
			SafeQueue<T, Container>() : std::queue<T, Container>() {}
			SafeQueue<T, Container>(const SafeQueue<T, Container> &) = default;
			~SafeQueue<T, Container>() noexcept = default;
			SafeQueue<T, Container> &operator=(const SafeQueue<T, Container> &) = default;

		/*
		 * Methods
		 */
		public:
			inline void safePush(const T &data) {
				std::unique_lock<std::mutex> lock(mutex);
				this->push(data);
			}

			inline void safePush(T &&data) {
				std::unique_lock<std::mutex> lock(mutex);
				this->push(std::forward<T>(data));
			}

			inline void safePop() {
				std::unique_lock<std::mutex> lock(mutex);
				this->pop();
			}

			inline bool safeEmpty() {
				std::unique_lock<std::mutex> lock(mutex);
				return this->empty();
			}

			inline T &safeFront() {
				std::unique_lock<std::mutex> lock(mutex);
				return this->front();
			}

			inline size_t safeSize() {
				std::unique_lock<std::mutex> lock(mutex);
				return this->size();
			}

		/*
		 * Field
		 */
		private:
			std::mutex mutex;
	};
}
