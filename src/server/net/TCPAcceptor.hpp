/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPAcceptor
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
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
		template<typename T>
		T *accept(const acceptCallback_t &callback);
		bool bind(int port);
		void close() { _acceptor.close(); }

	/*
	 * Fields
	 */
	private:
		NetworkService &_netService;
		boost::asio::ip::tcp::acceptor _acceptor;
};

template<>
inline TCPSocket *TCPAcceptor::accept(const acceptCallback_t &callback) {
	auto client = std::make_shared<TCPClient>(_netService);
	client->createSocket<TCPSocket>();

	_acceptor.async_accept(static_cast<TCPSocket*>(client->socket())->get(),
		[this, client, callback](const boost::system::error_code& error) {
			if (error) {
				std::cerr << "TCPSocket: " << error.message() << std::endl;
				return;
			}
			callback(client);
			accept<TCPSocket>(callback);
		});
	return static_cast<TCPSocket*>(client->socket());
}

template<>
inline SSLSocket *TCPAcceptor::accept(const acceptCallback_t &callback) {
	auto client = std::make_shared<TCPClient>(_netService);
	client->createSocket<SSLSocket>();

	_acceptor.async_accept(static_cast<SSLSocket*>(client->socket())->get(),
		[this, client, callback](const boost::system::error_code& error) {
			if (error) {
				std::cerr << "TCPSocket: " << error.message() << std::endl;
				return;
			}
			callback(client);
			accept<SSLSocket>(callback);
		});
	return static_cast<SSLSocket*>(client->socket());
}
}
