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
#include <boost/optional.hpp>

#include "NetworkService.hpp"
#include "ISocket.hpp"

#pragma once

namespace Zia::net {
struct SSLConf {
	std::string certFile;
	std::string keyFile;
	std::string dhFile;
	std::string verifFile;
};

class SSLSocket : public ISocket {
	public:
		SSLSocket(NetworkService&, boost::asio::ssl::context&);
		~SSLSocket() noexcept = default;
		SSLSocket() = delete;
		SSLSocket(const SSLSocket&) = delete;
		SSLSocket(SSLSocket&&) = default;
		SSLSocket &operator=(const SSLSocket&) = delete;
		SSLSocket &operator=(SSLSocket&&) = default;

	/*
	 * Methods
	 */
	public:
		bool connect(int, const std::string& = "127.0.0.1") override;
		void setReceive(const std::function<void(const char *, size_t)>&) override;
		void setDisconnect(const std::function<void(ISocket*)>&) override;
		void disconnect() override;
		size_t send(const char *, size_t) override;
		size_t send(const std::string&) override;
		auto &get() { return _socket.lowest_layer(); };

	private:
		void handleHandshake(const boost::system::error_code&);
		void handleReceive(const boost::system::error_code&, size_t) override;
		void handleSend(const boost::system::error_code&) override;

	/*
	 * Fields
	 */
	private:
		NetworkService &_service;
		boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;
		boost::asio::ip::tcp::resolver _resolver;
		char _buffer[READ_SIZE + 1];
		std::function<void(const char *, size_t)> _recvCallback;
		std::function<void(SSLSocket*)> _discCallback;
		std::string _ipAddr;
		int _port;
};
}
