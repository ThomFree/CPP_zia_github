/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** UDPSocket
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "NetworkService.hpp"
#include "ISocket.hpp"

namespace net {
	class UDPSocket : public net::ISocket {
	public:
		UDPSocket(net::NetworkService &netservice);
		UDPSocket(net::NetworkService &netservice, const std::string &ip);
		~UDPSocket();

	public:
		bool connect(const std::string &ip, int port) final;
		bool bind(int port = 0) final;
		bool receive(net::ReceiveCallbackFn onReceiveCallback, void *data = nullptr) final;
		int send(const std::string &data) final;
		int send(const char *data, size_t len) final;
		inline int getPort() const { return _port; }

	private:
		void handleReceive(const boost::system::error_code& error, size_t bytes_transferred);

	private:
		int _port;
		boost::asio::ip::udp::socket _socket;
		net::ReceiveCallbackFn _onReceiveCallback;
		void *_callbackData;
		std::string _myIP;
		char _receiveBuffer[net::read_size + 1];
		boost::asio::ip::udp::endpoint _remoteEndpoint;
		boost::asio::ip::udp::endpoint _myEndpoint;
	};
}