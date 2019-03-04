/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** Client
*/

#include <iostream>
#include "Client.hpp"

namespace Zia {

Client::Client(unsigned int id, std::shared_ptr<net::TCPClient> &sock) : _id(id), _tcpClient(sock) // TODO recevoir la config, les modules
{
	_tcpClient->socket()->setReceive([this](const char *data, size_t size) { readMsg(data, size); });
	_tcpClient->socket()->send("Hello World", 11);
}

Client::~Client()
{
}

void Client::readMsg(const char *data, size_t size)
{
	std::string msg(data, size);

	// DEBUG
	std::cout << "\t\t[Client] received : /" << msg << "/" << std::endl;
	// TODO start les modules ici (toute la pipeline)
}

void Client::stop()
{
	_tcpClient->socket()->disconnect();
}

}