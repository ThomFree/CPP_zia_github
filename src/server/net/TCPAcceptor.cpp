/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPAcceptor
*/

#include <iostream>
#include <utility>

#include "TCPAcceptor.hpp"

namespace Zia {
	namespace net {
		TCPAcceptor::TCPAcceptor(NetworkService &netService) : _netService(netService), _acceptor(_netService)
		{}

		bool TCPAcceptor::bind(int port) {
			boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
			try {
				_acceptor.open(endpoint.protocol());
				_acceptor.bind(endpoint);
				_acceptor.listen();
			} catch (const boost::system::system_error& error) {
				std::cerr << "TCPAcceptor: " << error.what() << std::endl;
				return false;
			}
			return true;
		}

		bool TCPAcceptor::accept(acceptCallback_t &&callback) {
			auto client = std::make_shared<Client>(TCPSocket(_netService));
			_acceptor.async_accept(client->socket()->get(),
				[this, client, &callback](const boost::system::error_code& error) {
					if (error) {
						std::cerr << "TCPSocket: " << error.message() << std::endl;
						return;
					}
					callback(client);
					accept(std::forward<acceptCallback_t>(callback));
				});
			return true;
		}
	}
}
