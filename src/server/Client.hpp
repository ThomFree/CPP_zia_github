/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <memory>
#include "net/TCPSocket.hpp"

#pragma once

namespace Zia {

class Client {
	public:
		Client(std::shared_ptr<net::TCPSocket> &sock);
		~Client();

	public:
		std::shared_ptr<net::TCPSocket> getSocket() const { return _tcpSocket; }

	private:
		std::shared_ptr<net::TCPSocket> _tcpSocket;
};

}