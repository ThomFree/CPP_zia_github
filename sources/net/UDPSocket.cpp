/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** UDPSocket
*/

#include <string.h>
#include <iostream>
#include "net/UDPSocket.hpp"

namespace net {
	UDPSocket::UDPSocket(net::NetworkService &netservice) :
	_socket(netservice, boost::asio::ip::udp::v4()),
	_myIP(net::localhost)
	{
	}

	UDPSocket::UDPSocket(net::NetworkService &netservice, const std::string &ip) :
	_socket(netservice, boost::asio::ip::udp::v4()),
	_myIP(ip)
	{
	}

	UDPSocket::~UDPSocket()
	{
		_socket.close();
	}

	bool UDPSocket::connect(const std::string &ip, int port) {
		_remoteEndpoint = boost::asio::ip::udp::endpoint(
			boost::asio::ip::address::from_string(ip), port);
		return true;
	}

	bool UDPSocket::bind(int port)
	{
		_myEndpoint = boost::asio::ip::udp::endpoint(
			boost::asio::ip::address::from_string(_myIP), port);
		try {
			_socket.bind(_myEndpoint);
		} catch (...) {
			std::cerr << "UDPSocket: Failed to bind to port " << port << std::endl;
			return false;
		}
		_port = _socket.local_endpoint().port();
		return true;
	}

	bool UDPSocket::receive(net::ReceiveCallbackFn onReceiveCallback, void *data)
	{
		if (getPort() == 0) {
			std::cerr << "UDPSocket: Socket must be bound to receive" << std::endl;
			return false;
		}
		_onReceiveCallback = onReceiveCallback;
		_callbackData = data;
		_socket.async_receive_from(boost::asio::buffer(_receiveBuffer),
			_myEndpoint,
			boost::bind(&net::UDPSocket::handleReceive,
				this,boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		return true;
	}

	int UDPSocket::send(const std::string &data)
	{
		return this->send(data.c_str(), data.length());
	}

	int UDPSocket::send(const char *data, size_t len)
	{
		if (_remoteEndpoint.port() == 0)
			return -1;
		boost::system::error_code err;
		auto payload = _socket.send_to(boost::asio::buffer(data, len),
			_remoteEndpoint, 0, err);
		if (!err)
			return payload;
		return -1;
	}

	void UDPSocket::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error) {
			_socket.async_receive_from(boost::asio::buffer(_receiveBuffer),
				_myEndpoint,
				boost::bind(&UDPSocket::handleReceive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			_receiveBuffer[bytes_transferred] = '\0';
			if (_onReceiveCallback)
				_onReceiveCallback(_receiveBuffer, bytes_transferred, _callbackData);
		} else
		std::cerr << "UDPSocket: " << error.message() << std::endl;
	}
}