/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** SSLSocket
*/

#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "NetworkService.hpp"
#include "ISocket.hpp"

#pragma once

namespace Zia::net {
class SSLSocket : public ISocket {
	public:
		using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;
		SSLSocket(NetworkService &, boost::asio::ssl::context &context);
		~SSLSocket() noexcept = default;
		SSLSocket() = delete;
		SSLSocket(const SSLSocket &) = delete;
		SSLSocket(SSLSocket &&) = default;
		SSLSocket &operator=(const SSLSocket &) = delete;
		SSLSocket &operator=(SSLSocket &&) = default;

	/*
	 * Methods
	 */
	public:
		bool connect(int, const std::string & = "127.0.0.1") override;
		void setReceive(std::function<void(const char *, size_t)> &&) override;
		void setDisconnect(std::function<void(ISocket*)> &&) override;
		void disconnect() override;
		size_t send(const char *, size_t) override;
		size_t send(const std::string &) override;
		SSLSocket::ssl_socket::lowest_layer_type &get() { return _socket.lowest_layer(); };

	private:
		void handleReceive(const boost::system::error_code&, size_t) override;
		void handleSend(const boost::system::error_code&) override;

	/*
	 * Fields
	 */
	private:
		ssl_socket _socket;
		boost::asio::ssl::context &_context;
		boost::asio::ip::tcp::resolver _resolver;
		char _buffer[READ_SIZE + 1];
		std::function<void(const char *, size_t)> _recvCallback;
		std::function<void(SSLSocket*)> _discCallback;
		std::string _ipAddr;
		int _port;
};
}
