/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** TCPSocket
*/

#include <iostream>
#include "net/TCPSocket.hpp"

namespace net {
	TCPSocket::TCPSocket(net::NetworkService &netservice) :
	_socket(netservice), _netservice(netservice), _resolver(netservice),
	_acceptor(netservice), _connectPort(-1),
	_onDisconnectionCallback(nullptr), _disconnectionCallbackData(nullptr)
	{}

	TCPSocket::~TCPSocket()
	{
		_socket.close();
	}

	bool TCPSocket::connect(const std::string &ip, int port)
	{
		try {
			boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
				ip, std::to_string(port));
			auto iterator = _resolver.resolve(query);
			boost::asio::connect(_socket, iterator);
		} catch(...) {
			return false;
		}
		_connectIP = ip;
		_connectPort = port;
		return true;
	}

	bool TCPSocket::bind(int port)
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
		try {
			_acceptor.open(endpoint.protocol());
			_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			_acceptor.bind(endpoint);
			_acceptor.listen();
		} catch (const boost::system::system_error& error) {
			std::cerr << "TCPSocket: " << error.what() << std::endl;
			return false;
		}
		return true;
	}

	bool TCPSocket::accept(ConnectCallbackFn onNewConnectionCallback, void *data)
	{
		auto clientSocket = std::make_shared<net::TCPSocket>(_netservice);
		_acceptor.async_accept(clientSocket->getRawSocket(),
			[this, clientSocket, onNewConnectionCallback, data](const boost::system::error_code& error) {
				if (error) {
					std::cerr << "TCPSocket: " << error.message() << std::endl;
					return;
				}
				onNewConnectionCallback(clientSocket, data);
				accept(onNewConnectionCallback, data);
			});
		return true;
	}

	void TCPSocket::disconnect()
	{
		std::cout << "Disconnect!" << std::endl;
		if (_onDisconnectionCallback)
			_onDisconnectionCallback(this, _disconnectionCallbackData);
	}

	void TCPSocket::onDisconnect(DisconnectCallbackFn onDisconnectCallback, void *data)
	{
		std::cout << "On disconnect" << std::endl;
		_onDisconnectionCallback = onDisconnectCallback;
		_disconnectionCallbackData = data;
	}

	TCPSocket::RawSocket &TCPSocket::getRawSocket()
	{
		return _socket;
	}

	bool TCPSocket::receive(TCPSocket::ReceiveCallbackFn onReceiveCallback, void *data)
	{
		_onReceiveCallback = onReceiveCallback;
		_receiveCallbackData = data;
		_socket.async_read_some(boost::asio::buffer(_receiveBuffer, net::read_size),
								boost::bind(&TCPSocket::handleReceive, this,
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred));
		return true;
	}

	int TCPSocket::send(const std::string &data)
	{
		return send(data.c_str(), data.length());
	}

	int TCPSocket::send(const char *data, size_t len)
	{
		if (!_socket.is_open()) {
			std::cerr << "TCPSocket: Socket must connect before send" << std::endl;
			return 0;
		}
		boost::asio::async_write(_socket, boost::asio::buffer(data, len),
								 boost::bind(&TCPSocket::handleSend, this,
											 boost::asio::placeholders::error));
		return len;
	}

	void TCPSocket::handleReceive(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error) {
			_socket.async_read_some(boost::asio::buffer(_receiveBuffer, net::read_size),
									boost::bind(&TCPSocket::handleReceive, this,
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
			_receiveBuffer[bytes_transferred] = '\0';
			if (_onReceiveCallback)
				_onReceiveCallback(_receiveBuffer, bytes_transferred, _receiveCallbackData);
		} else {
			if (((boost::asio::error::eof == error) || (boost::asio::error::connection_reset == error)) && _onDisconnectionCallback)
				_onDisconnectionCallback(this, _disconnectionCallbackData);
			else
				std::cerr << "TCPSocket: " << error.message() <<  std::endl;
		}
	}

	void TCPSocket::handleSend(const boost::system::error_code& error) const
	{
		if (error)
			std::cerr << "TCPSocket: " << error.message() << std::endl;
	}
}