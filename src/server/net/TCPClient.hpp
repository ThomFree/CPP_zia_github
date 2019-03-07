/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPClient
*/

#pragma once

#include <memory>

#include "net/NetworkService.hpp"
#include "net/TCPSocket.hpp"
#include "net/SSLSocket.hpp"

namespace Zia::net {

class TCPClient {
	public:
		explicit TCPClient(NetworkService &service) : _service(service) {};
		~TCPClient() noexcept = default;
		TCPClient(TCPClient &&) = default;
		TCPClient &operator=(const TCPClient &) = delete;

		TCPClient() = delete;
		TCPClient(const TCPClient &) = delete;
		TCPClient &operator=(TCPClient &&) = default;

	public:
		template<typename T> T *createSocket();

		ISocket *socket() const
		{
			return _socket.get();
		};

	private:
		NetworkService &_service;
		std::unique_ptr<ISocket> _socket = nullptr;

};

template<>
inline TCPSocket *TCPClient::createSocket()
{
	_socket = std::unique_ptr<TCPSocket>(new TCPSocket(_service));
	return static_cast<TCPSocket*>(_socket.get());
}

template<>
inline SSLSocket *TCPClient::createSocket()
{
	// @TODO: Set le contexte ssl (certificat ssl etc)
	boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
	_socket = std::unique_ptr<SSLSocket>(new SSLSocket(_service, context));
	return static_cast<SSLSocket*>(_socket.get());
}
}