/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** NetworkService
*/

#pragma once
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <iostream>

namespace Zia {
	namespace net {
		class NetworkService : public boost::asio::io_service {
		using signalCallbackFn = std::function<void()>;
		public:
			NetworkService(signalCallbackFn fnCallback = nullptr) : boost::asio::io_service(), _signals(*this, SIGINT) {
				_signals.async_wait([&](const boost::system::error_code &, int) {
					if (fnCallback)
						fnCallback();
					this->stop(); });
			}
			~NetworkService() {};

		/*
		 * Methods
		 */
		public:
			void run() { boost::asio::io_service::run(); }
			void stop() { boost::asio::io_service::stop(); }

		/*
		 * Fields
		 */
		private:
			boost::asio::signal_set _signals;
		};
	}
}