/*
** EPITECH PROJECT, 2019
** Zia
** File description:
** TCPSocket
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include "NetworkService.hpp"

namespace Zia {
	namespace net {
		static constexpr char google_dns_server[] = "8.8.8.8";
		static constexpr char localhost[] = "127.0.0.1";
		static constexpr size_t read_size = 1024;

		class TCPSocket {
		public:
			using ReceiveCallbackFn = std::function<void(const char *, int, void *)>;
			using ConnectCallbackFn = std::function<void(std::shared_ptr<TCPSocket>, void *)>;
			using DisconnectCallbackFn = std::function<void(TCPSocket*, void *)>;
			using RawSocket = boost::asio::ip::tcp::socket;

		public:
			explicit TCPSocket(NetworkService &netservice, bool isDebug = false);
			TCPSocket(const TCPSocket &) = default;
			~TCPSocket();
			TCPSocket &operator=(const TCPSocket &) = default;

		public:
			bool connect(const std::string &ip, int port); //
			bool bind(int port = 0); //
			bool accept(ConnectCallbackFn onNewConnectionCallback, void *data = nullptr); //
			bool receive(ReceiveCallbackFn onReceiveCallback, void *data = nullptr); //
			int send(const std::string &data); //
			int send(const char *data, size_t len); //
			void disconnect(); //
			void onDisconnect(DisconnectCallbackFn onDisconnectCallback, void *data = nullptr); //
			RawSocket &getRawSocket(); //

		private:
			void handleReceive(const boost::system::error_code& error, size_t bytes_transferred);
			void handleSend(const boost::system::error_code& error) const;

		private:
			boost::asio::ip::tcp::socket _socket; //
			NetworkService &_netservice; //
			boost::asio::ip::tcp::resolver _resolver; //
			boost::asio::ip::tcp::acceptor _acceptor; //
			std::string _connectIP; //
			int _connectPort; //
			char _receiveBuffer[net::read_size + 1]; //
			ReceiveCallbackFn _onReceiveCallback; //
			void *_receiveCallbackData; //
			DisconnectCallbackFn _onDisconnectionCallback; //
			void *_disconnectionCallbackData; //

			bool _isDebug;
		};
	}
}