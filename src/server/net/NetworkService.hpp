/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** NetworkService
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>

namespace Zia::net {
class NetworkService : public boost::asio::io_context {
	using signalCallbackFn = std::function<void()>;
	public:
		NetworkService(signalCallbackFn fnCallback = nullptr) : boost::asio::io_context(), _signals(*this, SIGINT) {
			_signals.async_wait([&, fnCallback](const boost::system::error_code &, int) {
				if (fnCallback)
					fnCallback();
				this->stop(); });
		}
		~NetworkService() {};

	/*
	 * Methods
	 */
	public:
		void run() { boost::asio::io_context::run(); }
		void stop() { boost::asio::io_context::stop(); }

	/*
	 * Fields
	 */
	private:
		boost::asio::signal_set _signals;
};
}