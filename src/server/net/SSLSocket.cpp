/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** SSLSocket
*/

#include <iostream>

#include "SSLSocket.hpp"

namespace Zia::net {
	SSLSocket::SSLSocket(NetworkService &netService, boost::asio::ssl::context &context)
		: _service(netService), _socket(_service, context), _resolver(netService)
	{

	}

	bool SSLSocket::connect(int port, const std::string &ipAddr) {
		try {
			boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
				ipAddr, std::to_string(port));
			auto iterator = _resolver.resolve(query);
			boost::asio::connect(_socket.lowest_layer(), iterator);
		} catch(...) {
			return false;
		}
		_ipAddr = ipAddr;
		_port = port;
		return true;
	}

	void SSLSocket::setReceive(const std::function<void(const char*, size_t)> &recvCallback) {
		_recvCallback = recvCallback;
		_socket.async_handshake(boost::asio::ssl::stream_base::server,
			boost::bind(&SSLSocket::handleHandshake, this,
			boost::asio::placeholders::error));
	}

	void SSLSocket::setDisconnect(const std::function<void(ISocket*)> &discCallback) {
		_discCallback = discCallback;
	}

	void SSLSocket::disconnect() {
		if (_discCallback) {
			_discCallback(this);
		}
	}

	void SSLSocket::handleHandshake(const boost::system::error_code &error)
	{
		if (!error) {
			_socket.async_read_some(boost::asio::buffer(_buffer, READ_SIZE),
			boost::bind(&SSLSocket::handleReceive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
		} else {
			std::cout << error.message() <<  std::endl;
			disconnect();
		}
	}

	void SSLSocket::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error) {
			_socket.async_read_some(boost::asio::buffer(_buffer, READ_SIZE),
									boost::bind(&SSLSocket::handleReceive, this,
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
			_buffer[bytes_transferred] = '\0';
			_recvCallback(_buffer, bytes_transferred);
		} else {
			std::cout << error.message() <<  std::endl;
			disconnect();
		}
	}

	size_t SSLSocket::send(const char *data, size_t len) {
		boost::asio::async_write(_socket, boost::asio::buffer(data, len),
								boost::bind(&SSLSocket::handleSend, this,
											boost::asio::placeholders::error));
		return len;
	}

	size_t SSLSocket::send(const std::string &data) {
		return send(data.data(), data.length());
	}

	void SSLSocket::handleSend(const boost::system::error_code& error) {
		if (error)
			std::cout << error.message() << std::endl;
	}
}