/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPSocket
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "NetworkService.hpp"
#include "ISocket.hpp"

#pragma once

namespace Zia::net {
class TCPSocket : public ISocket {
	public:
		explicit TCPSocket(NetworkService &);
		~TCPSocket() noexcept = default;
		TCPSocket() = delete;
		TCPSocket(const TCPSocket &) = default;
		TCPSocket(TCPSocket &&) = default;
		TCPSocket &operator=(const TCPSocket &) = default;
		TCPSocket &operator=(TCPSocket &&) = default;

	/*
	 * Methods
	 */
	public:
		bool connect(int, const std::string & = "127.0.0.1");
		void setReceive(std::function<void(const char *, size_t)> &&);
		void setDisconnect(std::function<void(ISocket*)> &&);
		void disconnect();
		size_t send(const char *, size_t);
		size_t send(const std::string &);
		boost::asio::ip::tcp::socket &get() { return _socket; };

	private:
		void handleReceive(const boost::system::error_code&, size_t);
		void handleSend(const boost::system::error_code&);

	/*
	 * Fields
	 */
	private:
		boost::asio::ip::tcp::socket _socket;
		boost::asio::ip::tcp::resolver _resolver;
		char _buffer[READ_SIZE + 1];
		std::function<void(const char *, size_t)> _recvCallback;
		std::function<void(TCPSocket*)> _discCallback;
		std::string _ipAddr;
		int _port;
};
}