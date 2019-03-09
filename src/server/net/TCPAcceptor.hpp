/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPAcceptor
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <memory>

#include "NetworkService.hpp"
#include "TCPSocket.hpp"
#include "SSLSocket.hpp"

#pragma once

namespace Zia::net {
class TCPAcceptor {
	using acceptCallback_t = std::function<void(std::shared_ptr<ISocket>)>;
	public:
		explicit TCPAcceptor(NetworkService &netService);
		~TCPAcceptor() noexcept = default;
		TCPAcceptor() = delete;
		TCPAcceptor(const TCPAcceptor &) = delete;
		TCPAcceptor(TCPAcceptor &&) = default;
		TCPAcceptor &operator=(const TCPAcceptor &) = delete;
		TCPAcceptor &operator=(TCPAcceptor &&) = default;

	/*
	 * Methods
	 */
	public:
		template<typename T>
		T *accept(const acceptCallback_t &callback);
		template<typename T>
		T *accept(const acceptCallback_t &callback, const net::SSLConf&);
		bool bind(int);
		void close() { _acceptor.close(); }

	/*
	 * Fields
	 */
	private:
		NetworkService &_netService;
		boost::asio::ip::tcp::acceptor _acceptor;
};

template<>
inline TCPSocket *TCPAcceptor::accept(const acceptCallback_t &callback)
{
	auto client = std::make_shared<TCPSocket>(_netService);

	_acceptor.async_accept(client->get(),
		[this, client, callback](const boost::system::error_code& error) {
			if (error) {
				std::cerr << "TCPSocket: " << error.message() << std::endl;
				return;
			}
			callback(client);
			accept<TCPSocket>(callback);
		});
	return client.get();
}

template<>
inline SSLSocket *TCPAcceptor::accept(const acceptCallback_t &callback, const net::SSLConf &conf)
{
	boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
	context.set_options(
		boost::asio::ssl::context::default_workarounds
		| boost::asio::ssl::context::no_sslv2
		| boost::asio::ssl::context::single_dh_use
	);
	context.use_certificate_chain_file(conf.certFile);
	context.use_private_key_file(conf.keyFile, boost::asio::ssl::context::pem);
	context.use_tmp_dh_file(conf.dhFile);
	context.set_verify_mode(boost::asio::ssl::context::verify_peer);
	context.load_verify_file(conf.verifFile);
	auto client = std::make_shared<SSLSocket>(_netService, context);
	_acceptor.async_accept(client->get(),
		[this, client, callback, conf](const boost::system::error_code& error) {
			if (error) {
				std::cerr << "TCPSocket: " << error.message() << std::endl;
				return;
			}
			callback(client);
			accept<SSLSocket>(callback, conf);
		});
	return client.get();
}
}
