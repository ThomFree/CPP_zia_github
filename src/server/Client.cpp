/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include "Client.hpp"

namespace Zia {

Client::Client(net::TCPSocket &&socket) : _socket(new net::TCPSocket(std::forward<net::TCPSocket>(socket)))
{
}

net::TCPSocket *Client::socket() const
{
	return _socket.get();
}

}