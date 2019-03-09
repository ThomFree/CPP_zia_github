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
		explicit TCPClient(NetworkService &service) : _service(service),
		_context(boost::asio::ssl::context::sslv23) {};
		~TCPClient() noexcept = default;
		TCPClient(TCPClient &&) = default;
		TCPClient &operator=(const TCPClient &) = delete;

		TCPClient() = delete;
		TCPClient(const TCPClient &) = delete;
		TCPClient &operator=(TCPClient &&) = default;

	public:
		std::string handle_password() const;
		template<typename T> T *createSocket();
		template<typename T> T *createSocket(boost::asio::ssl::context &context);

		ISocket *socket() const
		{
			return _socket.get();
		};

	private:
		NetworkService &_service;
		std::unique_ptr<ISocket> _socket = nullptr;
		boost::asio::ssl::context _context;

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
	_context.set_options(
		boost::asio::ssl::context::default_workarounds
		| boost::asio::ssl::context::no_sslv2
		| boost::asio::ssl::context::single_dh_use
	);
	_context.set_password_callback(boost::bind(&TCPClient::handle_password, this));
	_context.use_certificate_chain_file("./etc/zia/certs/myEncryptedSite/server.pem");
	_context.use_private_key_file("./etc/zia/certs/myEncryptedSite/server.key", boost::asio::ssl::context::pem);
	_context.use_tmp_dh_file("./etc/zia/certs/myEncryptedSite/dhparam.pem");

	_context.set_verify_mode(/*boost::asio::ssl::context::verify_fail_if_no_peer_cert | */boost::asio::ssl::context::verify_peer);
	_context.load_verify_file("./etc/zia/certs/myEncryptedSite/server.pem");

	_socket = std::unique_ptr<SSLSocket>(new SSLSocket(_service, _context));
	return static_cast<SSLSocket*>(_socket.get());
}
}