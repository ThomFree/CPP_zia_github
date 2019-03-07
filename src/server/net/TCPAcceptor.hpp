/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPAcceptor
*/

#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <memory>

#include "NetworkService.hpp"
#include "TCPClient.hpp"

namespace Zia::net {
class TCPAcceptor {
	using acceptCallback_t = std::function<void(std::shared_ptr<TCPClient>)>;
	public:
		explicit TCPAcceptor(NetworkService &netService);
		~TCPAcceptor() noexcept = default;
		TCPAcceptor() = delete;
		TCPAcceptor(const TCPAcceptor &) = delete;
		TCPAcceptor(TCPAcceptor &&) = default;
		TCPAcceptor &operator=(const TCPAcceptor &) = delete;
		TCPAcceptor &operator=(TCPAcceptor &&) = default;

	/*
		* Methods
		*/
	public:
		bool accept(const acceptCallback_t &callback);
		bool bind(int port);
		inline void cancel() { _acceptor.cancel(); }
		inline void close() { _acceptor.close(); }

	/*
		* Fields
		*/
	private:
		NetworkService &_netService;
		boost::asio::ip::tcp::acceptor _acceptor;
};
}
