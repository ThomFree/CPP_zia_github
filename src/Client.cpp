/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include "Client.hpp"

namespace Zia {
	namespace net {
		Client::Client(TCPSocket &&socket) : _socket(new TCPSocket(std::forward<TCPSocket>(socket)))
		{
			std::cout << "Created new client" << std::endl;
		}

		TCPSocket *Client::socket() const {
			return _socket.get();
		}
	}
}