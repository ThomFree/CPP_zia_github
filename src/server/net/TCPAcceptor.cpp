/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPAcceptor
*/

#include <iostream>
#include <utility>

#include "TCPAcceptor.hpp"

namespace Zia::net {
TCPAcceptor::TCPAcceptor(NetworkService &netService) : _netService(netService), _acceptor(_netService)
{}

bool TCPAcceptor::bind(int port) {
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	try {
		_acceptor.open(endpoint.protocol());
		_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true)); // REUSE // FOR DEBUG ONLY // DON T DELETE PLEASE <3
		_acceptor.bind(endpoint);
		_acceptor.listen();
	} catch (const std::runtime_error& error) {
		// BUG DON'T UNCOMMENT
		// std::cerr << "TCPAcceptor: " << error.what() << std::endl; ----> /!\ the error is not defined if bind failed (don't know why)
		return false;
	}
	return true;
}
}
