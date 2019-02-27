/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPSocket
*/

#include <iostream>

#include "TCPSocket.hpp"

namespace Zia {
	namespace net {
		TCPSocket::TCPSocket(NetworkService &netService) : _socket(netService), _resolver(netService)
		{
		}

		bool TCPSocket::connect(int port, const std::string &ipAddr) {
			try {
				boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
					ipAddr, std::to_string(port));
				auto iterator = _resolver.resolve(query);
				boost::asio::connect(_socket, iterator);
			} catch(...) {
				return false;
			}
			_ipAddr = ipAddr;
			_port = port;
			return true;
		}

		void TCPSocket::setReceive(std::function<void(const char*, size_t)> &&recvCallback) {
			_recvCallback = recvCallback;
			_socket.async_read_some(boost::asio::buffer(_buffer, READ_SIZE),
									boost::bind(&TCPSocket::handleReceive, this,
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
		}

		void TCPSocket::setDisconnect(std::function<void(TCPSocket*)> &&discCallback) {
			_discCallback = discCallback;
		}

		void TCPSocket::disconnect() {
			_discCallback(this);
		}

		boost::asio::ip::tcp::socket &TCPSocket::get() {
			return _socket;
		}

		void TCPSocket::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) {
			if (!error) {
				_socket.async_read_some(boost::asio::buffer(_buffer, READ_SIZE),
										boost::bind(&TCPSocket::handleReceive, this,
													boost::asio::placeholders::error,
													boost::asio::placeholders::bytes_transferred));
				_buffer[bytes_transferred] = '\0';
					_recvCallback(_buffer, bytes_transferred);
			} else {
				if (((boost::asio::error::eof == error) || (boost::asio::error::connection_reset == error)))
					disconnect();
				else
					std::cerr << "TCPSocket: " << error.message() <<  std::endl;
			}
		}

		size_t TCPSocket::send(const char *data, size_t len) {
			if (!_socket.is_open()) {
				std::cerr << "TCPSocket: Socket must connect before send" << std::endl;
				return 0;
			}
			boost::asio::async_write(_socket, boost::asio::buffer(data, len),
									boost::bind(&TCPSocket::handleSend, this,
												boost::asio::placeholders::error));
			return len;
		}

		size_t TCPSocket::send(const std::string &data) {
			return send(data.data(), data.length());
		}

		void TCPSocket::handleSend(const boost::system::error_code& error) {
			if (error)
				std::cerr << "TCPSocket: " << error.message() << std::endl;
		}
	}
}