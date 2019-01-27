/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** TCPSocket
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "NetworkService.hpp"
#include "ISocket.hpp"

namespace net {
	class TCPSocket : public ISocket {
	public:
		explicit TCPSocket(net::NetworkService &netservice);
		TCPSocket(const TCPSocket &) = default;
		~TCPSocket();
		TCPSocket &operator=(const TCPSocket &) = default;

	public:
		bool connect(const std::string &ip, int port) final;
		bool bind(int port = 0) final;
		bool accept(ConnectCallbackFn onNewConnectionCallback, void *data = nullptr);
		bool receive(net::ReceiveCallbackFn onReceiveCallback, void *data = nullptr) final;
		int send(const std::string &data) final;
		int send(const char *data, size_t len) final;
		void disconnect();
		void onDisconnect(ConnectCallbackFn onDisconnectCallback, void *data = nullptr);
		net::RawSocket &getRawSocket();

	private:
		void handleReceive(const boost::system::error_code& error, size_t bytes_transferred);
		void handleSend(const boost::system::error_code& error) const;

	private:
		boost::asio::ip::tcp::socket _socket;
		net::NetworkService &_netservice;
		boost::asio::ip::tcp::resolver _resolver;
		boost::asio::ip::tcp::acceptor _acceptor;
		std::string _connectIP;
		int _connectPort;
		char _receiveBuffer[net::read_size + 1];
		net::ReceiveCallbackFn _onReceiveCallback;
		void *_receiveCallbackData;
		net::ConnectCallbackFn _onDisconnectionCallback;
		void *_disconnectionCallbackData;
	};
}