/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <memory>
#include "net/TCPClient.hpp"

#pragma once

namespace Zia {

class Client {
	public:
		Client(unsigned int id, std::shared_ptr<net::TCPClient> &sock);
		~Client();

	public:
		std::shared_ptr<net::TCPClient> getSocket() const { return _tcpClient; }
		void readMsg(const char *data, size_t size);
		void stop();

	private:
		unsigned int _id;
		std::shared_ptr<net::TCPClient> _tcpClient;
};

}