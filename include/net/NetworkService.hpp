/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** NetworkService
*/

#pragma once
#include <boost/asio/signal_set.hpp>

namespace Zia {
	namespace net {
		class NetworkService : public boost::asio::io_service {
		using signalCallbackFn = std::function<void()>;
		public:
			NetworkService(signalCallbackFn fnCallback = nullptr) : boost::asio::io_service(), _signals(*this, SIGINT) {
				_signals.async_wait([&](const boost::system::error_code &, int) {
					std::cout << "Constructor with CB" << std::endl;
					if (fnCallback)
						fnCallback();
					this->stop(); });
			}
			~NetworkService() { std::cout << "[ NS destructor called. ]" << std::endl; };

		public:
			inline void run() { boost::asio::io_service::run(); }

			inline void stop() { boost::asio::io_service::stop(); }

		private:
			boost::asio::signal_set _signals;
		};
	}
}