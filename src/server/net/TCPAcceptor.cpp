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
		{
			std::cout << "[ TCP Acceptor constructed. ]" << std::endl; // DEBUG
		}

		bool TCPAcceptor::bind(int port) {
			boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
			try {
				_acceptor.open(endpoint.protocol());
				_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true)); // REUSE ADDR // DEBUG
				_acceptor.bind(endpoint);
				_acceptor.listen();
			} catch (const boost::system::system_error& error) {
				std::cerr << "TCPAcceptor: " << error.what() << std::endl;
				return false;
			}
			std::cout << "[ TCP Acceptor binded on " << port << " ]" << std::endl; // DEBUG
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
					std::cout << "[ TCP Acceptor accepted new Client {" << client.get() << "}. ]" << std::endl; // DEBUG
					accept(std::forward<acceptCallback_t>(callback));
				});
			return true;
		}
	}
}
