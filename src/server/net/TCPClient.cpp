/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** TCPClient
*/

#include "TCPClient.hpp"

namespace Zia::net {

TCPClient::TCPClient(net::TCPSocket &&socket) : _socket(new net::TCPSocket(std::forward<net::TCPSocket>(socket)))
{
}

net::TCPSocket *TCPClient::socket() const
{
	return _socket.get();
}

}